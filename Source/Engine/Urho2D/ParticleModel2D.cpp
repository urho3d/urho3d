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
#include "FileSystem.h"
#include "ParticleModel2D.h"
#include "ResourceCache.h"
#include "StringUtils.h"
#include "Sprite2D.h"
#include "XMLFile.h"

#include "DebugNew.h"

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

ParticleModel2D::ParticleModel2D(Context* context) :
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
    rotatePerSecond_(0.0f),
    rotatePerSecondVariance_(0.0f),
    blendMode_(BLEND_ALPHA),
    rotationStart_(0.0f),
    rotationStartVariance_(0.0f),
    rotationEnd_(0.0f),
    rotationEndVariance_(0.0f)
{
}

ParticleModel2D::~ParticleModel2D()
{
}

void ParticleModel2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ParticleModel2D>();
}

bool ParticleModel2D::Load(Deserializer& source)
{
    XMLFile xmlFile(context_);
    if (!xmlFile.Load(source))
        return false;

    XMLElement rootElem = xmlFile.GetRoot("particleEmitterConfig");
    if (!rootElem)
        return false;

    String texture = rootElem.GetChild("texture").GetAttribute("name");
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    sprite_= cache->GetResource<Sprite2D>(GetParentPath(GetName()) + texture);
    if (!sprite_)
        return false;

    sourcePositionVariance_ = ReadVector2(rootElem.GetChild("sourcePositionVariance"));

    speed_ = rootElem.GetChild("speed").GetFloat("value");
    speedVariance_ = rootElem.GetChild("speedVariance").GetFloat("value");
    
    particleLifeSpan_ = Max(0.01f, rootElem.GetChild("particleLifeSpan").GetFloat("value"));
    particleLifespanVariance_ = rootElem.GetChild("particleLifespanVariance").GetFloat("value");
    
    angle_ = 360.0f - rootElem.GetChild("angle").GetFloat("value");
    angleVariance_ = rootElem.GetChild("angleVariance").GetFloat("value");
    
    gravity_ = ReadVector2(rootElem.GetChild("gravity"));

    radialAcceleration_ = rootElem.GetChild("radialAcceleration").GetFloat("value");
    tangentialAcceleration_ = -rootElem.GetChild("tangentialAcceleration").GetFloat("value");
    
    radialAccelVariance_ = rootElem.GetChild("radialAccelVariance").GetFloat("value");
    tangentialAccelVariance_ = rootElem.GetChild("tangentialAccelVariance").GetFloat("value");

    startColor_ = ReadColor(rootElem.GetChild("startColor"));
    startColorVariance_ = ReadColor(rootElem.GetChild("startColorVariance"));
    
    finishColor_ = ReadColor(rootElem.GetChild("finishColor"));
    finishColorVariance_ = ReadColor(rootElem.GetChild("finishColorVariance"));

    maxParticles_ = rootElem.GetChild("maxParticles").GetInt("value");
    
    startParticleSize_ = rootElem.GetChild("startParticleSize").GetFloat("value");
    startParticleSizeVariance_ = rootElem.GetChild("startParticleSizeVariance").GetFloat("value");
    
    finishParticleSize_ = rootElem.GetChild("finishParticleSize").GetFloat("value");
    FinishParticleSizeVariance_ = rootElem.GetChild("FinishParticleSizeVariance").GetFloat("value");
    
    duration_ = M_INFINITY;
    if (rootElem.HasChild("duration"))
    {
        float duration = rootElem.GetChild("duration").GetFloat("value");
        if (duration > 0.0f)
            duration_ = duration;
    }


    emitterType_ = (EmitterType2D)rootElem.GetChild("emitterType").GetInt("value");
    
    maxRadius_ = rootElem.GetChild("maxRadius").GetFloat("value");
    maxRadiusVariance_ = rootElem.GetChild("maxRadiusVariance").GetFloat("value");
    minRadius_ = rootElem.GetChild("minRadius").GetFloat("value");

    rotatePerSecond_ = -rootElem.GetChild("rotatePerSecond").GetFloat("value");
    rotatePerSecondVariance_ = rootElem.GetChild("rotatePerSecondVariance").GetFloat("value");
    
    int blendFuncSource = rootElem.GetChild("blendFuncSource").GetInt("value");
    int blendFuncDestination = rootElem.GetChild("blendFuncDestination").GetInt("value");
    blendMode_ = BLEND_ALPHA;
    for (int i = 0; i < MAX_BLENDMODES; ++i)
    {
        if (blendFuncSource == srcBlendFuncs[i] && blendFuncDestination == destBlendFuncs[i])
        {
            blendMode_ = (BlendMode)i;
            break;
        }
    }

    rotationStart_ = -rootElem.GetChild("rotationStart").GetFloat("value");
    rotationStartVariance_ = rootElem.GetChild("rotationStartVariance").GetFloat("value");
    
    rotationEnd_ = -rootElem.GetChild("rotationEnd").GetFloat("value");
    rotationEndVariance_ = rootElem.GetChild("rotationEndVariance").GetFloat("value");

    return true;
}

bool ParticleModel2D::Save(Serializer& dest) const
{
    return false;
}

void ParticleModel2D::SetSourcePositionVariance(const Vector2& sourcePositionVariance)
{
    sourcePositionVariance_ = sourcePositionVariance;
}

void ParticleModel2D::SetSpeed(float speed)
{
    speed_ = speed;
}

void ParticleModel2D::SetSpeedVariance(float speedVariance)
{
    speedVariance_ = speedVariance;
}

void ParticleModel2D::SetParticleLifeSpan(float particleLifeSpan)
{
    particleLifeSpan_ = particleLifeSpan;
}

void ParticleModel2D::SetParticleLifespanVariance(float particleLifespanVariance)
{
    particleLifespanVariance_ = particleLifespanVariance;
}

void ParticleModel2D::SetAngle(float angle)
{
    angle_ = angle;
}

void ParticleModel2D::SetAngleVariance(float angleVariance)
{
    angleVariance_ = angleVariance;
}

void ParticleModel2D::SetGravity(const Vector2& gravity)
{
    gravity_ = gravity;
}

void ParticleModel2D::SetRadialAcceleration(float radialAcceleration)
{
    radialAcceleration_ = radialAcceleration;
}

void ParticleModel2D::SetTangentialAcceleration(float tangentialAcceleration)
{
    tangentialAcceleration_ = tangentialAcceleration;
}

void ParticleModel2D::SetRadialAccelVariance(float radialAccelVariance)
{
    radialAccelVariance_ = radialAccelVariance;
}

void ParticleModel2D::SetTangentialAccelVariance(float tangentialAccelVariance)
{
    tangentialAccelVariance_ = tangentialAccelVariance;
}

void ParticleModel2D::SetStartColor(const Color& startColor)
{
    startColor_ = startColor;
}

void ParticleModel2D::SetStartColorVariance(const Color& startColorVariance)
{
    startColorVariance_ = startColorVariance;
}

void ParticleModel2D::SetFinishColor(const Color& finishColor)
{
    finishColor_ = finishColor;
}

void ParticleModel2D::SetFinishColorVariance(const Color& finishColorVariance)
{
    finishColorVariance_ = finishColorVariance;
}

void ParticleModel2D::SetMaxParticles(int maxParticles)
{
    maxParticles_ = maxParticles;
}

void ParticleModel2D::SetStartParticleSize(float startParticleSize)
{
    startParticleSize_ = startParticleSize;
}

void ParticleModel2D::SetStartParticleSizeVariance(float startParticleSizeVariance)
{
    startParticleSizeVariance_ = startParticleSizeVariance;
}

void ParticleModel2D::SetFinishParticleSize(float finishParticleSize)
{
    finishParticleSize_ = finishParticleSize;
}

void ParticleModel2D::SetFinishParticleSizeVariance(float FinishParticleSizeVariance)
{
    FinishParticleSizeVariance_ = FinishParticleSizeVariance;
}

void ParticleModel2D::SetDuration(float duration)
{
    duration_ = duration;
}

void ParticleModel2D::SetEmitterType(EmitterType2D emitterType)
{
    emitterType_ = emitterType;
}

void ParticleModel2D::SetMaxRadius(float maxRadius)
{
    maxRadius_ = maxRadius;
}

void ParticleModel2D::SetMaxRadiusVariance(float maxRadiusVariance)
{
    maxRadiusVariance_ = maxRadiusVariance;
}

void ParticleModel2D::SetMinRadius(float minRadius)
{
    minRadius_ = minRadius;
}

void ParticleModel2D::SetRotatePerSecond(float rotatePerSecond)
{
    rotatePerSecond_ = rotatePerSecond;
}

void ParticleModel2D::SetRotatePerSecondVariance(float rotatePerSecondVariance)
{
    rotatePerSecondVariance_ = rotatePerSecondVariance;
}

void ParticleModel2D::SetBlendMode(BlendMode blendMode)
{
    blendMode_ = blendMode;
}

void ParticleModel2D::SetRotationStart(float rotationStart)
{
    rotationStart_ = rotationStart;
}

void ParticleModel2D::SetRotationStartVariance(float rotationStartVariance)
{
    rotationStartVariance_ = rotationStartVariance;
}

void ParticleModel2D::SetRotationEnd(float rotationEnd)
{
    rotationEnd_ = rotationEnd;
}

void ParticleModel2D::SetRotationEndVariance(float rotationEndVariance)
{
    rotationEndVariance_ = rotationEndVariance;
}

Color ParticleModel2D::ReadColor(const XMLElement& element) const
{
    Color color;
    color.r_ = element.GetFloat("red");
    color.g_ = element.GetFloat("green");
    color.b_ = element.GetFloat("blue");
    color.a_ = element.GetFloat("alpha");
    return color;
}

Vector2 ParticleModel2D::ReadVector2(const XMLElement& element) const
{
    // Flip y.
    return Vector2(element.GetFloat("x"), -element.GetFloat("y"));
}

}
