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

#pragma once

#include "BillboardSet.h"

/// Determines the emitter shape
enum EmitterType
{
    EMITTER_POINT,
    EMITTER_SPHERE,
    EMITTER_BOX
};

/// One particle in the particle system
struct Particle
{
    /// Velocity
    Vector3 velocity_;
    /// Original billboard size
    Vector2 size_;
    /// Time elapsed from creation
    float timer_;
    /// Lifetime
    float timeToLive_;
    /// Size scaling value
    float scale_;
    /// Rotation speed
    float rotationSpeed_;
    /// Current color fade index
    unsigned colorIndex_;
    /// Current texture animation index
    unsigned texIndex_;
};

/// Texture animation
struct TextureAnimation
{
    Rect uv_;
    float time_;
};

class ResourceCache;
class XMLFile;
class XMLElement;

/// Particle emitter component
class ParticleEmitter : public BillboardSet
{
    OBJECT(ParticleEmitter);
    
public:
    /// Construct
    ParticleEmitter(Context* context);
    /// Destruct
    virtual ~ParticleEmitter();
    /// Register object factory
    static void RegisterObject(Context* context);
    
    /// Update the particle system. Is called from HandleScenePostUpdate()
    void Update(float timeStep);
    /// Load emitter parameters from an XML file. Return true if successful
    bool LoadParameters(XMLFile* file);
    /// %Set emitter active/inactive state and optionally reset active/inactive timer
    void SetActive(bool enable, bool resetPeriod = false);
    
    /// Return parameter XML file
    XMLFile* GetParameters() const { return parameterSource_; }
    /// Return number of particles
    unsigned GetNumParticles() const { return particles_.Size(); }
    /// Return whether emitter is active
    bool IsActive() const { return active_; }
    
    /// %Set parameter source attribute
    void SetParameterSourceAttr(ResourceRef value);
    /// %Set particles attribute
    void SetParticlesAttr(PODVector<unsigned char> value);
    /// Return parameter source attribute
    ResourceRef GetParameterSourceAttr() const;
    /// Return particles attribute
    PODVector<unsigned char> GetParticlesAttr() const;
    
protected:
    /// Handle node being assigned
    virtual void OnNodeSet(Node* node);
    
    /// %Set number of particles
    void SetNumParticles(int num);
    /// %Set color of particles
    void SetParticleColor(const Color& color);
    /// %Set color fade of particles
    void SetParticleColors(const Vector<ColorFade>& colors);
    /// Create a new particle. Return true if there was room
    bool EmitNewParticle();
    /// Return a free particle index
    unsigned GetFreeParticle() const;
    /// Read a float range from an XML element
    void GetFloatMinMax(const XMLElement& element, float& minValue, float& maxValue);
    /// Read a Vector2 range from an XML element
    void GetVector2MinMax(const XMLElement& element, Vector2& minValue, Vector2& maxValue);
    /// Read a Vector3 from an XML element
    void GetVector3MinMax(const XMLElement& element, Vector3& minValue, Vector3& maxValue);
    
private:
    /// Handle scene post-update event
    void HandleScenePostUpdate(StringHash eventType, VariantMap& eventData);
    
    /// Parameter XML file
    SharedPtr<XMLFile> parameterSource_;
    /// Particles
    PODVector<Particle> particles_;
    /// Color fade range
    Vector<ColorFade> colors_;
    /// Texture animation
    Vector<TextureAnimation> textureAnimation_;
    /// Emitter shape
    EmitterType emitterType_;
    /// Emitter size
    Vector3 emitterSize_;
    /// Particle direction minimum
    Vector3 directionMin_;
    /// Particle direction maximum
    Vector3 directionMax_;
    /// Particle constant force
    Vector3 constanceForce_;
    /// Particle size minimum
    Vector2 sizeMin_;
    /// Particle size maximum
    Vector2 sizeMax_;
    /// Particle velocity damping force
    float dampingForce_;
    /// Emitter radius if spherical
    float emitterRadius_;
    /// Active/inactive period timer
    float periodTimer_;
    /// New particle emission timer
    float emissionTimer_;
    /// Active period
    float activeTime_;
    /// Inactive period
    float inactiveTime_;
    /// Emission interval minimum
    float intervalMin_;
    /// Emission interval maximum
    float intervalMax_;
    /// Particle time to live minimum
    float timeToLiveMin_;
    /// Particle time to live maximum
    float timeToLiveMax_;
    /// Particle velocity minimum
    float velocityMin_;
    /// Particle velocityy maximum
    float velocityMax_;
    /// Particle rotation angle minimum
    float rotationMin_;
    /// Particle rotation angle maximum
    float rotationMax_;
    /// Particle rotation speed minimum
    float rotationSpeedMin_;
    /// Particle rotation speed maximum
    float rotationSpeedMax_;
    /// Particle size additive parameter
    float sizeAdd_;
    /// Particle size multiplicative parameter
    float sizeMul_;
    /// Emitter active/inactive state
    bool active_;
    /// Update when invisible flag
    bool updateInvisible_;
    /// Rendering renderer framenumber on which was last updated
    unsigned lastUpdateFrameNumber_;
};
