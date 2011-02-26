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

#ifndef ENGINE_PARTICLEEMITTER_H
#define ENGINE_PARTICLEEMITTER_H

#include "BillboardSet.h"
#include "EventListener.h"

//! Determines the emitter shape
enum EmitterType
{
    EMITTER_POINT,
    EMITTER_SPHERE,
    EMITTER_BOX
};

//! One particle in the particle system
struct Particle
{
    //! Velocity
    Vector3 mVelocity;
    //! Original billboard size
    Vector2 mSize;
    //! Time elapsed from creation
    float mTimer;
    //! Lifetime
    float mTimeToLive;
    //! Size scaling value
    float mScale;
    //! Rotation speed
    float mRotationSpeed;
    //! Current color fade index
    unsigned mColorIndex;
    //! Current texture animation index
    unsigned mTexIndex;
};

//! Texture animation
struct TextureAnimation
{
    Rect mUV;
    float mTime;
};

class ResourceCache;
class XMLFile;
class XMLElement;

//! Particle emitter scene node
class ParticleEmitter : public BillboardSet, public EventListener
{
    DEFINE_TYPE(ParticleEmitter);
    
public:
    //! Construct with initial octant pointer and name
    ParticleEmitter(Octant* octant = 0, const std::string& name = std::string());
    
    //! Write component state to a stream
    virtual void save(Serializer& dest);
    //! Read component state from a stream
    virtual void load(Deserializer& source, ResourceCache* cache);
    //! Write component state to an XML element
    virtual void saveXML(XMLElement& dest);
    //! Read component state from an XML element
    virtual void loadXML(const XMLElement& source, ResourceCache* cache);
    //! Write a network update
    virtual bool writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info);
    //! Read a network update
    virtual void readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info);
    //! Return resource references
    virtual void getResourceRefs(std::vector<Resource*>& dest);
    
    //! Update the particle system. Is called from handleScenePostUpdate()
    void update(float timeStep);
    //! Load emitter parameters from an XML file
    void loadParameters(XMLFile* file, ResourceCache* cache);
    //! Set emitter active/inactive state and optionally reset active/inactive timer
    void setActive(bool enable, bool resetPeriod = false);
    
    //! Return parameter XML file
    XMLFile* getParameters() const { return mParameterSource; }
    //! Return number of particles
    unsigned getNumParticles() const { return mParticles.size(); }
    //! Return whether emitter is active
    bool isActive() const { return mActive; }
    
protected:
    //! Set number of particles
    void setNumParticles(int num);
    //! Set color of particles
    void setParticleColor(const Color& color);
    //! Set color fade of particles
    void setParticleColors(const std::vector<ColorFade>& colors);
    //! Create a new particle. Return true if there was room
    bool emitNewParticle();
    //! Return a free particle index
    unsigned getFreeParticle() const;
    //! Read a float range from an XML element
    void getFloatMinMax(const XMLElement& element, float& minValue, float& maxValue);
    //! Read a Vector2 range from an XML element
    void getVector2MinMax(const XMLElement& element, Vector2& minValue, Vector2& maxValue);
    //! Read a Vector3 from an XML element
    void getVector3MinMax(const XMLElement& element, Vector3& minValue, Vector3& maxValue);
    
private:
    //! Handle scene post-update event
    void handleScenePostUpdate(StringHash eventType, VariantMap& eventData);
    
    //! Parameter XML file
    SharedPtr<XMLFile> mParameterSource;
    //! Particles
    std::vector<Particle> mParticles;
    //! Color fade range
    std::vector<ColorFade> mColors;
    //! Texture animation
    std::vector<TextureAnimation> mTextureAnimation;
    //! Emitter shape
    EmitterType mEmitterType;
    //! Emitter size
    Vector3 mEmitterSize;
    //! Particle direction minimum
    Vector3 mDirectionMin;
    //! Particle direction maximum
    Vector3 mDirectionMax;
    //! Particle constant force
    Vector3 mConstantForce;
    //! Particle size minimum
    Vector2 mSizeMin;
    //! Particle size maximum
    Vector2 mSizeMax;
    //! Particle velocity damping force
    float mDampingForce;
    //! Emitter radius if spherical
    float mEmitterRadius;
    //! Active/inactive period timer
    float mPeriodTimer;
    //! New particle emission timer
    float mEmissionTimer;
    //! Active period
    float mActiveTime;
    //! Inactive period
    float mInactiveTime;
    //! Emission interval minimum
    float mIntervalMin;
    //! Emission interval maximum
    float mIntervalMax;
    //! Particle time to live minimum
    float mTimeToLiveMin;
    //! Particle time to live maximum
    float mTimeToLiveMax;
    //! Particle velocity minimum
    float mVelocityMin;
    //! Particle velocityy maximum
    float mVelocityMax;
    //! Particle rotation angle minimum
    float mRotationMin;
    //! Particle rotation angle maximum
    float mRotationMax;
    //! Particle rotation speed minimum
    float mRotationSpeedMin;
    //! Particle rotation speed maximum
    float mRotationSpeedMax;
    //! Particle size additive parameter
    float mSizeAdd;
    //! Particle size multiplicative parameter
    float mSizeMul;
    //! Emitter active/inactive state
    bool mActive;
    //! Update when invisible flag
    bool mUpdateInvisible;
    //! Rendering pipeline framenumber on which was last updated
    unsigned mLastUpdateFrameNumber;
};

#endif // ENGINE_PARTICLEEMITTER_H
