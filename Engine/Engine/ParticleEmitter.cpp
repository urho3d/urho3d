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
#include "Material.h"
#include "ParticleEmitter.h"
#include "Profiler.h"
#include "ReplicationUtils.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "XMLFile.h"

#include "DebugNew.h"

ParticleEmitter::ParticleEmitter(Octant* octant, const std::string& name) :
    BillboardSet(octant, name),
    mEmitterType(EMITTER_POINT),
    mEmitterSize(Vector3::sZero),
    mDirectionMin(Vector3(-1.0f, -1.0f, -1.0f)),
    mDirectionMax(Vector3(1.0f, 1.0f, 1.0f)),
    mConstantForce(Vector3::sZero),
    mSizeMin(Vector2(0.1f, 0.1f)),
    mSizeMax(Vector2(0.1f, 0.1f)),
    mDampingForce(0.0f),
    mEmitterRadius(0.0f),
    mPeriodTimer(0.0f),
    mEmissionTimer(0.0f),
    mActiveTime(0.0f),
    mInactiveTime(0.0f),
    mIntervalMin(0.1f),
    mIntervalMax(0.1f),
    mTimeToLiveMin(1.0f),
    mTimeToLiveMax(1.0f),
    mVelocityMin(1.0f),
    mVelocityMax(1.0f),
    mRotationMin(0.0f),
    mRotationMax(0.0f),
    mRotationSpeedMin(0.0f),
    mRotationSpeedMax(0.0f),
    mSizeAdd(0.0f),
    mSizeMul(1.0f),
    mActive(true),
    mUpdateInvisible(false),
    mLastUpdateFrameNumber(M_MAX_UNSIGNED)
{
    setParticleColor(Color(1.0f, 1.0f, 1.0f));
    setNumParticles(10);
    subscribeToEvent(EVENT_SCENEPOSTUPDATE, EVENT_HANDLER(ParticleEmitter, handleScenePostUpdate));
}

void ParticleEmitter::save(Serializer& dest)
{
    // Write BillboardSet properties
    BillboardSet::save(dest);
    
    // Write ParticleEmitter properties
    dest.writeStringHash(getResourceHash(mParameterSource));
    dest.writeFloat(mPeriodTimer);
    dest.writeFloat(mEmissionTimer);
    dest.writeBool(mActive);
    
    dest.writeVLE(mParticles.size());
    for (unsigned i = 0; i < mParticles.size(); ++i)
    {
        // Optimization: write only enabled particles
        if (mBillboards[i].mEnabled)
        {
            const Particle& particle = mParticles[i];
            dest.writeVector3(particle.mVelocity);
            dest.writeVector2(particle.mSize);
            dest.writeFloat(particle.mTimer);
            dest.writeFloat(particle.mTimeToLive);
            dest.writeFloat(particle.mScale);
            dest.writeFloat(particle.mRotationSpeed);
            dest.writeVLE(particle.mColorIndex);
        }
    }
}

void ParticleEmitter::load(Deserializer& source, ResourceCache* cache)
{
    // Read BillboardSet properties
    BillboardSet::load(source, cache);
    
    // Read ParticleEmitter properties
    loadParameters(cache->getResource<XMLFile>(source.readStringHash()), cache);
    mPeriodTimer = source.readFloat();
    mEmissionTimer = source.readFloat();
    mActive = source.readBool();
    
    mParticles.resize(source.readVLE());
    for (unsigned i = 0; i < mParticles.size(); ++i)
    {
        if (mBillboards[i].mEnabled)
        {
            Particle& particle = mParticles[i];
            particle.mVelocity = source.readVector3();
            particle.mSize = source.readVector2();
            particle.mTimer = source.readFloat();
            particle.mTimeToLive = source.readFloat();
            particle.mScale = source.readFloat();
            particle.mRotationSpeed = source.readFloat();
            particle.mColorIndex = source.readVLE();
        }
    }
}

void ParticleEmitter::saveXML(XMLElement& dest)
{
    // Write BillboardSet properties
    BillboardSet::saveXML(dest);
    
    // Write ParticleEmitter properties
    XMLElement emitterElem = dest.createChildElement("emitter");
    emitterElem.setString("name", getResourceName(mParameterSource));
    emitterElem.setFloat("periodtimer", mPeriodTimer);
    emitterElem.setFloat("emissiontimer", mEmissionTimer);
    emitterElem.setBool("active", mActive);
    
    for (unsigned i = 0; i < mParticles.size(); ++i)
    {
        XMLElement particleElem = dest.createChildElement("particle");
        // Optimization: write only enabled particles
        if (mBillboards[i].mEnabled)
        {
            const Particle& particle = mParticles[i];
            particleElem.setVector3("velocity", particle.mVelocity);
            particleElem.setVector2("size", particle.mSize);
            particleElem.setFloat("timer", particle.mTimer);
            particleElem.setFloat("ttl", particle.mTimeToLive);
            particleElem.setFloat("scale", particle.mScale);
            particleElem.setFloat("rotspeed", particle.mRotationSpeed);
            particleElem.setInt("color", particle.mColorIndex);
        }
    }
}

void ParticleEmitter::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read BillboardSet properties
    BillboardSet::loadXML(source, cache);
    
    // Read ParticleEmitter properties
    XMLElement emitterElem = source.getChildElement("emitter");
    loadParameters(cache->getResource<XMLFile>(emitterElem.getString("name")), cache);
    mPeriodTimer = emitterElem.getFloat("periodtimer");
    mEmissionTimer = emitterElem.getFloat("emissiontimer");
    mActive = emitterElem.getBool("active");
    setNumParticles(getNumBillboards());
    
    XMLElement particleElem = source.getChildElement("particle");
    unsigned index = 0;
    while ((particleElem) && (index < mParticles.size()))
    {
        Particle& particle = mParticles[index];
        particle.mVelocity = particleElem.getVector3("velocity");
        particle.mSize = particleElem.getVector2("size");
        particle.mTimer = particleElem.getFloat("timer");
        particle.mTimeToLive = particleElem.getFloat("ttl");
        particle.mScale = particleElem.getFloat("scale");
        particle.mRotationSpeed = particleElem.getFloat("rotspeed");
        particle.mColorIndex = particleElem.getInt("color");
        particleElem = particleElem.getNextElement("particle");
        ++index;
    }
}

bool ParticleEmitter::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    // Write BillboardSet properties and see if there were any changes
    bool prevBits = BillboardSet::writeNetUpdate(dest, destRevision, baseRevision, info);
    
    // Build bitmask of changed properties
    unsigned char bits = 0;
    checkStringHash(getResourceHash(mParameterSource), baseRevision, bits, 3);
    // Only replicate the active flag if both time periods are infinite (manually controlled),
    // otherwise let the emitter run by timer
    checkBool(mActive, baseRevision, bits, ((mActiveTime == 0.0f) && (mInactiveTime == 0.0f)) ? 2 : 0);
    checkBool(mUpdateInvisible, baseRevision, bits, 4);
    
    // Update replication state fully, and network stream by delta
    dest.writeUByte(bits);
    writeStringHashDelta(getResourceHash(mParameterSource), dest, destRevision, bits & 1);
    writeBoolDelta(mActive, dest, destRevision, bits & 2);
    writeBoolDelta(mActive, dest, destRevision, bits & 4);
    
    return prevBits || (bits != 0);
}

void ParticleEmitter::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
{
    // Read BillboardSet properties
    BillboardSet::readNetUpdate(source, cache, info);
    
    unsigned char bits = source.readUByte();
    if (bits & 1)
    {
        StringHash parameters = source.readStringHash();
        // There is possibility of receiving the same update twice, and this is fairly expensive, so check
        if (parameters != getResourceHash(mParameterSource))
            loadParameters(cache->getResource<XMLFile>(parameters), cache);
    }
    readBoolDelta(mActive, source, bits & 2);
    readBoolDelta(mUpdateInvisible, source, bits & 4);
}

void ParticleEmitter::update(float timeStep)
{
    // If this is a playback update, return so that we do not erroneously accelerate emitter animation
    if (isPlayback())
        return;
    
    // If no invisible update, check that the billboardset is in view (framenumber has changed)
    if (!mUpdateInvisible)
    {
        if (mViewFrameNumber == mLastUpdateFrameNumber)
            return;
    }
    mLastUpdateFrameNumber = mViewFrameNumber;
    
    PROFILE(ParticleEmitter_Update);
    
    // If size mismatch, correct it
    if (mParticles.size() != mBillboards.size())
        setNumBillboards(mParticles.size());
    
    bool needBillboardUpdate = false;
    
    // Check active/inactive period switching
    mPeriodTimer += timeStep;
    if (mActive)
    {
        if ((mActiveTime) && (mPeriodTimer >= mActiveTime))
        {
            mActive = false;
            mPeriodTimer -= mActiveTime;
        }
    }
    else
    {
        if ((mInactiveTime) && (mPeriodTimer >= mInactiveTime))
        {
            mActive = true;
            mPeriodTimer -= mInactiveTime;
        }
    }
    
    // Check for emitting a new particle
    if (mActive)
    {
        mEmissionTimer += timeStep;
        if (mEmissionTimer > 0.0f)
        {
            mEmissionTimer -= lerp(mIntervalMin, mIntervalMax, random(1.0f));
            if (emitNewParticle())
                needBillboardUpdate = true;
        }
    }
    
    // Update existing particles
    Vector3 relativeConstantForce = getWorldRotation().getInverse() * mConstantForce;
    // If billboards are not relative, apply scaling to the position update
    Vector3 scaleVector = Vector3::sUnity;
    if ((mScaleBillboards) && (!mBillboardsRelative))
        scaleVector = getWorldScale();
    
    for (unsigned i = 0; i < mParticles.size(); ++i)
    {
        Particle& particle = mParticles[i];
        Billboard& billboard = mBillboards[i];
        
        if (billboard.mEnabled)
        {
            needBillboardUpdate = true;
            
            // Time to live
            if (particle.mTimer >= particle.mTimeToLive)
            {
                billboard.mEnabled = false;
                continue;
            }
            particle.mTimer += timeStep;
            
            // Velocity & position
            if (mConstantForce != Vector3::sZero)
            {
                if (mBillboardsRelative)
                    particle.mVelocity += timeStep * relativeConstantForce;
                else
                    particle.mVelocity += timeStep * mConstantForce;
            }
            if (mDampingForce != 0.0f)
            {
                Vector3 force = -mDampingForce * particle.mVelocity;
                particle.mVelocity += timeStep * force;
            }
            billboard.mPosition += timeStep * particle.mVelocity * scaleVector;
            
            // Rotation
            billboard.mRotation += timeStep * particle.mRotationSpeed;
            
            // Scaling
            if ((mSizeAdd != 0.0f) || (mSizeMul != 1.0f))
            {
                particle.mScale += timeStep * mSizeAdd;
                if (mSizeMul != 1.0f)
                    particle.mScale *= (timeStep * (mSizeMul - 1.0f)) + 1.0f;
                billboard.mSize = particle.mSize * particle.mScale;
            }
            
            // Color interpolation
            unsigned& index = particle.mColorIndex;
            if (index < mColors.size())
            {
                if (index < mColors.size() - 1)
                {
                    if (particle.mTimer >= mColors[index + 1].mTime)
                        ++index;
                }
                if (index < mColors.size() - 1)
                    billboard.mColor = mColors[index].interpolate(mColors[index + 1], particle.mTimer);
                else
                    billboard.mColor = mColors[index].mColor;
            }
        }
    }
    
    if (needBillboardUpdate)
        updated();
}

void ParticleEmitter::loadParameters(XMLFile* file, ResourceCache* cache)
{
    if (!file)
        return;
    if (!cache)
        EXCEPTION("Null resource cache for ParticleEmitter");
    
    mParameterSource = file;
    XMLElement rootElem = mParameterSource->getRootElement();
    
    if (rootElem.hasChildElement("material"))
        setMaterial(cache->getResource<Material>(rootElem.getChildElement("material").getString("name")));
    
    if (rootElem.hasChildElement("sorting"))
        mBillboardsSorted = rootElem.getChildElement("sorting").getBool("enable");
        
    if (rootElem.hasChildElement("updateinvisible"))
        mUpdateInvisible = rootElem.getChildElement("updateinvisible").getBool("enable");
    
    if (rootElem.hasChildElement("relative"))
        mBillboardsRelative = rootElem.getChildElement("relative").getBool("enable");
    
    if (rootElem.hasChildElement("emittertype"))
    {
        std::string type = rootElem.getChildElement("emittertype").getStringLower("value");
        if (type == "point")
            mEmitterType = EMITTER_POINT;
        else if (type == "box")
            mEmitterType = EMITTER_BOX;
        else if (type == "sphere")
            mEmitterType = EMITTER_SPHERE;
        else
            EXCEPTION("Unknown particle emitter type " + type);
    }
    
    if (rootElem.hasChildElement("emittersize"))
        mEmitterSize = rootElem.getChildElement("emittersize").getVector3("value");
    
    if (rootElem.hasChildElement("direction"))
        getVector3MinMax(rootElem.getChildElement("direction"), mDirectionMin, mDirectionMax);
    
    if (rootElem.hasChildElement("constantforce"))
        mConstantForce = rootElem.getChildElement("constantforce").getVector3("value");
    
    if (rootElem.hasChildElement("dampingforce"))
        mDampingForce = rootElem.getChildElement("dampingforce").getFloat("value");
    
    if (rootElem.hasChildElement("activetime"))
        mActiveTime = rootElem.getChildElement("activetime").getFloat("value");
    if (mActiveTime < 0.0f)
        mActiveTime = M_INFINITY;
    
    if (rootElem.hasChildElement("inactivetime"))
        mInactiveTime = rootElem.getChildElement("inactivetime").getFloat("value");
    if (mInactiveTime < 0.0f)
        mInactiveTime = M_INFINITY;
    
    if (rootElem.hasChildElement("interval"))
        getFloatMinMax(rootElem.getChildElement("interval"), mIntervalMin, mIntervalMax);
    
    if (rootElem.hasChildElement("particlesize"))
        getVector2MinMax(rootElem.getChildElement("particlesize"), mSizeMin, mSizeMax);
    
    if (rootElem.hasChildElement("timetolive"))
        getFloatMinMax(rootElem.getChildElement("timetolive"), mTimeToLiveMin, mTimeToLiveMax);
    
    if (rootElem.hasChildElement("velocity"))
        getFloatMinMax(rootElem.getChildElement("velocity"), mVelocityMin, mVelocityMax);
    
    if (rootElem.hasChildElement("rotation"))
        getFloatMinMax(rootElem.getChildElement("rotation"), mRotationMin, mRotationMax);
    
    if (rootElem.hasChildElement("rotationspeed"))
        getFloatMinMax(rootElem.getChildElement("rotationspeed"), mRotationSpeedMin, mRotationSpeedMax);
    
    if (rootElem.hasChildElement("sizedelta"))
    {
        XMLElement deltaElem = rootElem.getChildElement("sizedelta");
        if (deltaElem.hasAttribute("add"))
            mSizeAdd = deltaElem.getFloat("add");
        if (deltaElem.hasAttribute("mul"))
            mSizeMul = deltaElem.getFloat("mul");
    }
    
    if (rootElem.hasChildElement("color"))
        setParticleColor(rootElem.getChildElement("color").getColor("value"));
    
    if (rootElem.hasChildElement("colorfade"))
    {
        std::vector<ColorFade> fades;
        XMLElement colorFadeElem = rootElem.getChildElement("colorfade");
        while (colorFadeElem)
        {
            ColorFade fade;
            fade.mColor = colorFadeElem.getColor("color");
            fade.mTime = colorFadeElem.getFloat("time");
            fades.push_back(fade);
            
            colorFadeElem = colorFadeElem.getNextElement("colorfade");
        }
        setParticleColors(fades);
    }
}

void ParticleEmitter::setNumParticles(unsigned num)
{
    mParticles.resize(num);
    setNumBillboards(num);
}

void ParticleEmitter::setEmitterType(EmitterType type)
{
    mEmitterType = type;
}

void ParticleEmitter::setEmitterSize(const Vector3& size)
{
    mEmitterSize = Vector3(
        max(size.mX, 0.0f),
        max(size.mY, 0.0f),
        max(size.mZ, 0.0f)
    );
    
    mEmitterRadius = max(mEmitterSize.mX, max(mEmitterSize.mY, mEmitterSize.mZ)) * 0.5f;
}

void ParticleEmitter::setActiveTime(float time)
{
    mActiveTime = max(time, 0.0f);
}

void ParticleEmitter::setInactiveTime(float time)
{
    mInactiveTime = max(time, 0.0f);
}

void ParticleEmitter::setInterval(float minValue, float maxValue)
{
    mIntervalMin = max(minValue, M_EPSILON);
    mIntervalMax = max(maxValue, M_EPSILON);
}

void ParticleEmitter::setInterval(float value)
{
    setInterval(value, value);
}

void ParticleEmitter::setTimeToLive(float minValue, float maxValue)
{
    mTimeToLiveMin = max(minValue, 0.0f);
    mTimeToLiveMax = max(minValue, 0.0f);
}

void ParticleEmitter::setTimeToLive(float value)
{
    setTimeToLive(value, value);
}

void ParticleEmitter::setDirection(const Vector3& minValue, const Vector3& maxValue)
{
    mDirectionMin = minValue;
    mDirectionMax = maxValue;
}

void ParticleEmitter::setDirection(const Vector3& value)
{
    setDirection(value, value);
}

void ParticleEmitter::setConstantForce(const Vector3& force)
{
    mConstantForce = force;
}

void ParticleEmitter::setDampingForce(float force)
{
    mDampingForce = force;
}

void ParticleEmitter::setParticleVelocity(float minValue, float maxValue)
{
    mVelocityMin = minValue;
    mVelocityMax = maxValue;
}

void ParticleEmitter::setParticleVelocity(float value)
{
    setParticleVelocity(value, value);
}

void ParticleEmitter::setParticleRotation(float minValue, float maxValue)
{
    mRotationMin = minValue;
    mRotationMax = maxValue;
}

void ParticleEmitter::setParticleRotation(float value)
{
    setParticleRotation(value, value);
}

void ParticleEmitter::setParticleRotationSpeed(float minValue, float maxValue)
{
    mRotationSpeedMin = minValue;
    mRotationSpeedMax = maxValue;
}

void ParticleEmitter::setParticleRotationSpeed(float value)
{
    setParticleRotationSpeed(value, value);
}

void ParticleEmitter::setParticleSize(const Vector2& minValue, const Vector2& maxValue)
{
    mSizeMin = minValue;
    mSizeMax = maxValue;
}

void ParticleEmitter::setParticleSize(const Vector2& value)
{
    setParticleSize(value, value);
}

void ParticleEmitter::setParticleSize(float minValue, float maxValue)
{
    mSizeMin = Vector2(minValue, minValue);
    mSizeMax = Vector2(maxValue, maxValue);
}

void ParticleEmitter::setParticleSize(float value)
{
    setParticleSize(value, value);
}

void ParticleEmitter::setParticleSizeDelta(float addValue, float mulValue)
{
    mSizeAdd = addValue;
    mSizeMul = mulValue;
}

void ParticleEmitter::setParticleColor(const Color& color)
{
    ColorFade newColor;
    newColor.mColor = color;
    newColor.mTime = 0.0f;
    
    mColors.clear();
    mColors.push_back(newColor);
}

void ParticleEmitter::setParticleColors(const std::vector<ColorFade>& colors)
{
    if (!colors.size())
        return;
    
    mColors = colors;
}

void ParticleEmitter::setActive(bool enable, bool resetPeriod)
{
    if ((enable != mActive) || (resetPeriod))
    {
        mActive = enable;
        mPeriodTimer = 0.0f;
    }
}

void ParticleEmitter::setUpdateInvisible(bool enable)
{
    mUpdateInvisible = enable;
}

void ParticleEmitter::handleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace ScenePostUpdate;
    
    // Check that the scene matches
    Scene* scene = mEntity ? mEntity->getScene() : 0;
    if (eventData[P_SCENE].getPtr() == (void*)scene)
        update(eventData[P_TIMESTEP].getFloat());
}

bool ParticleEmitter::emitNewParticle()
{
    unsigned index = getFreeParticle();
    if (index >= mParticles.size())
        return false;
    Particle& particle = mParticles[index];
    Billboard& billboard = mBillboards[index];
    
    Vector3 startPos;
    Vector3 startDir;
    
    switch (mEmitterType)
    {
    case EMITTER_POINT:
        startPos = Vector3::sZero;
        break;
        
    case EMITTER_BOX:
        startPos = Vector3(
            random(mEmitterSize.mX) - mEmitterSize.mX * 0.5f,
            random(mEmitterSize.mY) - mEmitterSize.mY * 0.5f,
            random(mEmitterSize.mZ) - mEmitterSize.mZ * 0.5f
        );
        break;
        
    case EMITTER_SPHERE:
        {
            Vector3 dir(
                random(2.0f) - 1.0f,
                random(2.0f) - 1.0f,
                random(2.0f) - 1.0f
            );
            dir.normalize();
            startPos = random(mEmitterRadius) * dir;
        }
        break;
    }
    
    startDir = Vector3(
        lerp(mDirectionMin.mX, mDirectionMax.mX, random(1.0f)),
        lerp(mDirectionMin.mY, mDirectionMax.mY, random(1.0f)),
        lerp(mDirectionMin.mZ, mDirectionMax.mZ, random(1.0f))
    );
    startDir.normalize();
    
    if (!mBillboardsRelative)
    {
        startPos = getWorldTransform() * startPos;
        startDir = getWorldRotation() * startDir;
    };
    
    particle.mVelocity = lerp(mVelocityMin, mVelocityMax, random(1.0f)) * startDir;
    particle.mSize = mSizeMin.lerp(mSizeMax, random(1.0f));
    particle.mTimer = 0.0f;
    particle.mTimeToLive = lerp(mTimeToLiveMin, mTimeToLiveMax, random(1.0f));
    particle.mScale = 1.0f;
    particle.mRotationSpeed = lerp(mRotationSpeedMin, mRotationSpeedMax, random(1.0f));
    particle.mColorIndex = 0;
    billboard.mPosition = startPos;
    billboard.mSize = mParticles[index].mSize;
    billboard.mRotation = lerp(mRotationMin, mRotationMax, random(1.0f));
    billboard.mColor = mColors[0].mColor;
    billboard.mEnabled = true;
    return true;
}

unsigned ParticleEmitter::getFreeParticle() const
{
    for (unsigned i = 0; i < mBillboards.size(); ++i)
    {
        if (!mBillboards[i].mEnabled)
            return i;
    }
    
    return M_MAX_UNSIGNED;
}

void ParticleEmitter::getFloatMinMax(const XMLElement& element, float& minValue, float& maxValue)
{
    if (element.isNull())
        return;
    
    if (element.hasAttribute("value"))
        minValue = maxValue = element.getFloat("value");
    
    if ((element.hasAttribute("min")) && (element.hasAttribute("max")))
    {
        minValue = element.getFloat("min");
        maxValue = element.getFloat("max");
    }
}

void ParticleEmitter::getVector2MinMax(const XMLElement& element, Vector2& minValue, Vector2& maxValue)
{
    if (element.isNull())
        return;
    
    if (element.hasAttribute("value"))
        minValue = maxValue = element.getVector2("value");
    
    if ((element.hasAttribute("min")) && (element.hasAttribute("max")))
    {
        minValue = element.getVector2("min");
        maxValue = element.getVector2("max");
    }
}

void ParticleEmitter::getVector3MinMax(const XMLElement& element, Vector3& minValue, Vector3& maxValue)
{
    if (element.isNull())
        return;
    
    if (element.hasAttribute("value"))
        minValue = maxValue = element.getVector3("value");
    
    if ((element.hasAttribute("min")) && (element.hasAttribute("max")))
    {
        minValue = element.getVector3("min");
        maxValue = element.getVector3("max");
    }
}
