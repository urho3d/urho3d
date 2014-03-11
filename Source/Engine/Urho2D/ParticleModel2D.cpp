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
    blendMode_(BLEND_ALPHA),
    duration_(-1.0f),
    emitterType_(EMITTER_TYPE_GRAVITY),
    sourcePositionVariance_(Vector2::ZERO),
    maxParticles_(32),
    particleLifeSpan_(1.0f),
    particleLifeSpanVariance_(0.0f),
    startParticleSize_(1.0f),
    startParticleSizeVariance_(0.0f),
    endParticleSize_(0.0f),
    endParticleSizeVariance_(0.0f),
    emitAngle_(0.0f),
    emitAngleVariance_(0.0f),
    speed_(100.0f),
    speedVariance_(0.0f),
    gravity_(Vector2::ZERO),
    radialAcceleration_(0.0f),
    radialAccelerationVariance_(0.0f),
    tangentialAcceleration_(0.0f),
    tangentialAccelerationVariance_(0.0f),
    maxRadius_(100.0f),
    maxRadiusVariance_(0.0f),
    minRadius_(0.0f),
    rotatePerSecond_(0.0f),
    rotatePerSecondVariance_(0.0f),
    startColor_(Color::WHITE),
    startColorVariance_(Color::TRANSPARENT),
    endColor_(Color::WHITE),
    endColorVariance_(Color::TRANSPARENT)
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

    XMLElement plistElem = xmlFile.GetRoot("plist");
    if (!plistElem)
        return false;

    XMLElement dictElem = plistElem.GetChild();
    if (!dictElem || dictElem.GetName() != "dict")
        return false;

    VariantMap keyValueMapping;
    XMLElement keyElem = dictElem.GetChild();
    while (keyElem)
    {
        if (keyElem.GetName() != "key")
            return false;

        XMLElement valueElem = keyElem.GetNext();
        if (!valueElem)
            return false;

        String key = keyElem.GetValue();
        String type = valueElem.GetName();
        String value = valueElem.GetValue();

        if (type == "integer")
            keyValueMapping[key] = ToInt(value);
        else if (type == "real")
            keyValueMapping[key] = ToFloat(value);
        else
            keyValueMapping[key] = value;

        keyElem = valueElem.GetNext();
    }

    const String& textureFileName = keyValueMapping["textureFileName"].GetString();
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    sprite_= cache->GetResource<Sprite2D>(textureFileName);
    if (!sprite_)
        return false;

    int blendFuncSource = keyValueMapping["blendFuncSource"].GetInt();
    int blendFuncDestination = keyValueMapping["blendFuncDestination"].GetInt();
    blendMode_ = BLEND_ALPHA;
    for (int i = 0; i < MAX_BLENDMODES; ++i)
    {
        if (blendFuncSource == srcBlendFuncs[i] && blendFuncDestination == destBlendFuncs[i])
        {
            blendMode_ = (BlendMode)i;
            break;
        }
    }

    // Apply model scale
    const float modelScale = 0.01f;

    duration_ = keyValueMapping["duration"].GetFloat();
    emitterType_ = (EmitterType2D)(int)keyValueMapping["emitterType"].GetFloat();

    sourcePositionVariance_.x_ = keyValueMapping["sourcePositionVariancex"].GetFloat() * modelScale;
    sourcePositionVariance_.y_ = keyValueMapping["sourcePositionVariancey"].GetFloat() * modelScale;

    maxParticles_ = (unsigned)keyValueMapping["maxParticles"].GetFloat();
    particleLifeSpan_ = keyValueMapping["particleLifespan"].GetFloat();

    particleLifeSpanVariance_ = keyValueMapping["particleLifespanVariance"].GetFloat();
    startParticleSize_ = keyValueMapping["startParticleSize"].GetFloat() * modelScale;
    startParticleSizeVariance_ = keyValueMapping["startParticleSizeVariance"].GetFloat() * modelScale;
    endParticleSize_ = keyValueMapping["finishParticleSize"].GetFloat() * modelScale;
    endParticleSizeVariance_ = keyValueMapping["finishParticleSizeVariance"].GetFloat() * modelScale;
    emitAngle_ = keyValueMapping["angle"].GetFloat();
    emitAngleVariance_ = keyValueMapping["angleVariance"].GetFloat();

    speed_ = keyValueMapping["speed"].GetFloat() * modelScale;
    speedVariance_ = keyValueMapping["speedVariance"].GetFloat() * modelScale;

    gravity_.x_ = keyValueMapping["gravityx"].GetFloat() * modelScale;
    gravity_.y_ = keyValueMapping["gravityy"].GetFloat() * modelScale;

    radialAcceleration_ = keyValueMapping["radialAcceleration"].GetFloat() * modelScale;
    radialAccelerationVariance_ = keyValueMapping["radialAccelVariance"].GetFloat() * modelScale;
    tangentialAcceleration_ = keyValueMapping["tangentialAcceleration"].GetFloat() * modelScale;
    tangentialAccelerationVariance_ = keyValueMapping["tangentialAccelVariance"].GetFloat() * modelScale;

    maxRadius_ = keyValueMapping["maxRadius"].GetFloat() * modelScale;
    maxRadiusVariance_ = keyValueMapping["maxRadiusVariance"].GetFloat() * modelScale;
    minRadius_ = keyValueMapping["minRadius"].GetFloat() * modelScale;
    rotatePerSecond_ = keyValueMapping["rotatePerSecond"].GetFloat();
    rotatePerSecondVariance_ = keyValueMapping["rotatePerSecondVariance"].GetFloat();

    startColor_.r_ = keyValueMapping["startColorRed"].GetFloat();
    startColor_.g_ = keyValueMapping["startColorGreen"].GetFloat();
    startColor_.b_ = keyValueMapping["startColorBlue"].GetFloat();
    startColor_.a_ = keyValueMapping["startColorAlpha"].GetFloat();

    startColorVariance_.r_ = keyValueMapping["startColorVarianceRed"].GetFloat();
    startColorVariance_.g_ = keyValueMapping["startColorVarianceGreen"].GetFloat();
    startColorVariance_.b_ = keyValueMapping["startColorVarianceBlue"].GetFloat();
    startColorVariance_.a_ = keyValueMapping["startColorVarianceAlpha"].GetFloat();

    endColor_.r_ = keyValueMapping["finishColorRed"].GetFloat();
    endColor_.g_ = keyValueMapping["finishColorGreen"].GetFloat();
    endColor_.b_ = keyValueMapping["finishColorBlue"].GetFloat();
    endColor_.a_ = keyValueMapping["finishColorAlpha"].GetFloat();

    endColorVariance_.r_ = keyValueMapping["finishColorVarianceRed"].GetFloat();
    endColorVariance_.g_ = keyValueMapping["finishColorVarianceGreen"].GetFloat();
    endColorVariance_.b_ = keyValueMapping["finishColorVarianceBlue"].GetFloat();
    endColorVariance_.a_ = keyValueMapping["finishColorVarianceAlpha"].GetFloat();

    return true;
}

bool ParticleModel2D::Save(Serializer& dest) const
{
    return false;
}

Sprite2D* ParticleModel2D::GetSprite() const
{
    return sprite_;
}

}
