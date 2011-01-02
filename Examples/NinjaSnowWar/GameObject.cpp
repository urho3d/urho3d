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
#include "AnimatedModel.h"
#include "Animation.h"
#include "AnimationState.h"
#include "Deserializer.h"
#include "Engine.h"
#include "Entity.h"
#include "Exception.h"
#include "GameObject.h"
#include "GameEvents.h"
#include "Light.h"
#include "MemoryBuffer.h"
#include "Ninja.h"
#include "PhysicsEvents.h"
#include "PositionalChannel.h"
#include "Potion.h"
#include "ReplicationUtils.h"
#include "ResourceCache.h"
#include "RigidBody.h"
#include "Sound.h"
#include "Scene.h"
#include "Serializer.h"
#include "SnowBall.h"
#include "SnowCrate.h"
#include "XMLElement.h"

#include "DebugNew.h"

GameObject::GameObject() :
    mDuration(-1.0f),
    mMaxHealth(1),
    mHealth(1),
    mCanCollide(true),
    mOnGround(false),
    mIsSliding(false),
    mSide(SIDE_NEUTRAL),
    mOrigin(0),
    mLastDamageOrigin(0)
{
    // Do not replicate the GameObject component by default
    setNetFlags(NET_SYNCTONONE);
    
    subscribeToEvent(EVENT_PHYSICSPOSTSTEP, EVENT_HANDLER(GameObject, handlePhysicsPostStep));
    subscribeToEvent(EVENT_ENTITYCOLLISION, EVENT_HANDLER(GameObject, handleEntityCollision));
}

GameObject::~GameObject()
{
}

void GameObject::save(Serializer& dest)
{
    // Write Component properties
    Component::save(dest);
    
    // Write GameObject properties
    dest.writeFloat(mDuration);
    dest.writeInt(mSide);
    dest.writeInt(mHealth);
    dest.writeInt(mMaxHealth);
    dest.writeBool(mOnGround);
    dest.writeBool(mIsSliding);
    dest.writeBool(mCanCollide);
    dest.writeUInt(mOrigin);
    dest.writeUInt(mLastDamageOrigin);
    dest.writeInt(mPoints);
}

void GameObject::load(Deserializer& source, ResourceCache* cache)
{
    // Read Component properties
    Component::load(source, cache);
    
    // Read GameObject properties
    mDuration = source.readFloat();
    mSide = source.readInt();
    mHealth = source.readInt();
    mMaxHealth = source.readInt();
    mOnGround = source.readBool();
    mIsSliding = source.readBool();
    mCanCollide = source.readBool();
    mOrigin = source.readUInt();
    mLastDamageOrigin = source.readUInt();
    mPoints = source.readInt();
}

void GameObject::saveXML(XMLElement& dest)
{
    // Write Component properties
    Component::saveXML(dest);
    
    // Write GameObject properties
    XMLElement gameObjectElem = dest.createChildElement("gameobject");
    gameObjectElem.setFloat("duration", mDuration);
    gameObjectElem.setInt("side", mSide);
    gameObjectElem.setInt("health", mHealth);
    gameObjectElem.setInt("maxhealth", mMaxHealth);
    gameObjectElem.setBool("onground", mOnGround);
    gameObjectElem.setBool("issliding", mIsSliding);
    gameObjectElem.setBool("cancollide", mCanCollide);
    gameObjectElem.setInt("origin", mOrigin);
    gameObjectElem.setInt("damageorigin", mLastDamageOrigin);
    gameObjectElem.setInt("points", mPoints);
}

void GameObject::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read Component properties
    Component::loadXML(source, cache);
    
    // Read GameObject properties
    XMLElement gameObjectElem = source.getChildElement("gameobject");
    mDuration = gameObjectElem.getFloat("duration");
    mSide = gameObjectElem.getInt("side");
    mHealth = gameObjectElem.getInt("health");
    mMaxHealth = gameObjectElem.getInt("maxhealth");
    mOnGround = gameObjectElem.getBool("onground");
    mIsSliding = gameObjectElem.getBool("issliding");
    mCanCollide = gameObjectElem.getBool("cancollide");
    mOrigin = gameObjectElem.getInt("origin");
    mLastDamageOrigin = gameObjectElem.getInt("damageorigin");
    mPoints = gameObjectElem.getInt("points");
}

bool GameObject::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    // Build bitmask of changed properties
    unsigned char bits = 0;
    checkFloat(mDuration, -1.0f, baseRevision, bits, 1);
    checkInt(mSide, SIDE_NEUTRAL, baseRevision, bits, 2);
    checkInt(mHealth, 1, baseRevision, bits, 4);
    checkInt(mMaxHealth, 1, baseRevision, bits, 8);
    checkBool(mCanCollide, true, baseRevision, bits, 16);
    checkUInt(mOrigin, 0, baseRevision, bits, 32);
    checkUInt(mLastDamageOrigin, 0, baseRevision, bits, 64);
    checkInt(mPoints, 0, baseRevision, bits, 128);
    
    // Update replication state fully, and network stream by delta
    dest.writeUByte(bits);
    writeFloatDelta(mDuration, dest, destRevision, bits & 1);
    writeIntDelta(mSide, dest, destRevision, bits & 2);
    writeIntDelta(mHealth, dest, destRevision, bits & 4);
    writeIntDelta(mMaxHealth, dest, destRevision, bits & 8);
    writeBoolDelta(mCanCollide, dest, destRevision, bits & 16);
    writeUIntDelta(mOrigin, dest, destRevision, bits & 32);
    writeUIntDelta(mLastDamageOrigin, dest, destRevision, bits & 64);
    writeIntDelta(mPoints, dest, destRevision, bits & 128);
    
    return bits != 0;
}

void GameObject::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
{
    unsigned char bits = source.readUByte();
    readFloatDelta(mDuration, source, bits & 1);
    readIntDelta(mSide, source, bits & 2);
    readIntDelta(mHealth, source, bits & 4);
    readIntDelta(mMaxHealth, source, bits & 8);
    if (bits & 16)
        setCanCollide(source.readBool());
    readUIntDelta(mOrigin, source, bits & 32);
    readUIntDelta(mLastDamageOrigin, source, bits & 64);
    readIntDelta(mPoints, source, bits & 128);
}

void GameObject::create(const Vector3& position, const Quaternion& orientation)
{
    if (!mEntity)
        EXCEPTION("GameObject must belong to an entity before being created");
    
    // Subclass specific creation (create entity, bodies & geometries)
    onCreate(position, orientation);
    
    // Initialize health
    setHealth(mMaxHealth);
    
    // Send creation event
    using namespace Create;
    
    VariantMap eventData;
    eventData[P_OBJECT] = (void*)this;
    sendEvent(EVENT_CREATE, eventData);
}

void GameObject::postUpdateFixed(float time)
{
    bool goOn = true;
    
    // Perform subclass specific update
    goOn = onUpdate(time);
    
    // Reset ground/sliding flag for the next frame
    RigidBody* body = getBody();
    if (body)
    {
        if (body->isActive())
        {
            mOnGround = false;
            mIsSliding = false;
        }
        else
        {
            // If body is sleeping, assume it rests on ground
            mOnGround = true;
            mIsSliding = false;
        }
    }
    
    // Decrement lifetime duration
    if (mDuration >= 0)
    {
        mDuration -= time;
        if (mDuration <= 0) goOn = false;
    }
    
    // Kind of hack: if there is a light attached, decrease its intensity
    Light* light = mEntity->getComponent<Light>();
    if (light)
        light->setColor(light->getColor() * max(1.0f - time * 10.0f, 0.0f));
    
    // Only remove the entity if we are authoritative
    if ((!isProxy()) && (!goOn))
    {
        onRemove();
        
        // Send removal event
        using namespace Remove;
        
        VariantMap eventData;
        eventData[P_OBJECT] = (void*)this;
        sendEvent(EVENT_REMOVE, eventData);
        
        // Remove through the scene. Note: no operations on the GameObject are safe after this!
        getScene()->removeEntity(mEntity);
        return;
    }
}

void GameObject::setCanCollide(bool enable)
{
    mCanCollide = enable;
    RigidBody* body = getBody();
    // Collision to static objects always on, enable/disable dynamic object collision as necessary
    if (body)
        body->setCollisionMask(enable ? 3 : 2);
}

void GameObject::setHealth(int health)
{
    if (health < 0) health = 0;
    mHealth = health;
}

bool GameObject::damage(int damage, GameObject* source)
{
    // Only take damage if the object allows it
    if (onDamage(damage))
    {
        mHealth -= damage;
        if (mHealth < 0)
            mHealth = 0;
      
        // Record who is responsible for last damage
        if (source)
            mLastDamageOrigin = source->mOrigin;
        else
            mLastDamageOrigin = 0;
        
        using namespace Damage;
        
        VariantMap eventData;
        eventData[P_OBJECT] = (void*)this;
        sendEvent(EVENT_DAMAGE, eventData);
        
        return true;
    }
    
    return false;
}

bool GameObject::heal(int amount)
{
    if (mHealth >= mMaxHealth) return false;
    
    // Only heal if the object allows it
    if (onHeal(amount))
    {
        mHealth += amount;
        if (mHealth > mMaxHealth) mHealth = mMaxHealth;
        
        using namespace Heal;
        
        VariantMap eventData;
        eventData[P_OBJECT] = (void*)this;
        sendEvent(EVENT_HEAL, eventData);
        
        return true;
    }
    return false;
}

void GameObject::enableAnim(const std::string& name, bool restart)
{
    AnimatedModel* model = mEntity->getComponent<AnimatedModel>();
    if (!model)
        return;
    
    AnimationState* state = model->getAnimationState(name);
    if (state)
    {
        // Start from beginning if restart explicitly requested
        if (restart)
            state->setTime(0.0f);
        state->setWeight(1.0f);
    }
    else
    {
        AnimationState* state = model->addAnimationState(getAnim(name));
        state->setWeight(1.0f);
    }
}

void GameObject::enableOnlyAnim(const std::string& name, bool restart)
{
    AnimatedModel* model = mEntity->getComponent<AnimatedModel>();
    if (!model)
        return;
    
    // Enable only the animation we want
    enableAnim(name, restart);
    
    // Disable all others
    std::vector<AnimationState*> states = model->getAnimationStates();
    for (unsigned i = 0; i < states.size(); ++i)
    {
        if (states[i]->getAnimation()->getName() != name)
            model->removeAnimationState(states[i]);
    }
}

void GameObject::enableOnlyAnimSmooth(const std::string& name, bool restart, float time)
{
    AnimatedModel* model = mEntity->getComponent<AnimatedModel>();
    if (!model)
        return;
    
    AnimationState* state = model->getAnimationState(name);
    if (!state)
        state = model->addAnimationState(getAnim(name));
    if (restart)
        state->setTime(0.0f);
    
    // Increase weight of the animation we're activating, start from 0 if was disabled
    state->addWeight(time);
    
    // Decrease weight of all the rest, until at weight 0 and can be disabled
    std::vector<AnimationState*> states = model->getAnimationStates();
    for (unsigned i = 0; i < states.size(); ++i)
    {
        if (states[i]->getAnimation()->getName() != name)
        {
            states[i]->addWeight(-time);
            if (states[i]->getWeight() == 0.0f)
                model->removeAnimationState(states[i]);
        }
    }
}

void GameObject::disableAnim(const std::string& name)
{
    AnimatedModel* model = mEntity->getComponent<AnimatedModel>();
    if (!model)
        return;
    model->removeAnimationState(name);
}

void GameObject::advanceAnim(const std::string& name, bool looped, float time)
{
    AnimatedModel* model = mEntity->getComponent<AnimatedModel>();
    if (!model)
        return;
    AnimationState* state = model->getAnimationState(name);
    if (state)
    {
        state->setLooped(looped);
        state->addTime(time);
    }
}

void GameObject::setAnimWeight(const std::string& name, float weight)
{
    AnimatedModel* model = mEntity->getComponent<AnimatedModel>();
    if (!model)
        return;
    AnimationState* state = model->getAnimationState(name);
    if (state)
        state->setWeight(weight);
}

void GameObject::setAnimPriority(const std::string& name, int priority)
{
    AnimatedModel* model = mEntity->getComponent<AnimatedModel>();
    if (!model)
        return;
    AnimationState* state = model->getAnimationState(name);
    if (state)
        state->setPriority(priority);
}

void GameObject::playSound(const std::string& name)
{
   // Need an unique name to ensure proper replication (we potentially have many sounds in the same entity)
    PositionalChannel* channel = createComponent<PositionalChannel>(mEntity->getUniqueComponentName());
    channel->setAutoRemove(true);
    // Attach to the first scenenode component we find from the entity
    Node* node = mEntity->getDerivedComponent<Node>();
    if (node)
        node->addChild(channel);
    else
        return;
    Sound* sound = getResourceCache()->getResource<Sound>(name);
    channel->setDistanceAttenuation(200.0f, 5000.0f, 1.0f);
    channel->play(sound, sound->getFrequency());
}

void GameObject::playSound(const std::string& name, const Vector3& position)
{
    // Need an unique name to ensure proper replication (we potentially have many sounds in the same entity)
    PositionalChannel* channel = createComponent<PositionalChannel>(mEntity->getUniqueComponentName());
    Sound* sound = getResourceCache()->getResource<Sound>(name);
    channel->setAutoRemove(true);
    channel->setPosition(position);
    channel->setDistanceAttenuation(200.0f, 5000.0f, 1.0f);
    channel->play(sound, sound->getFrequency());
}

const std::string& GameObject::getName() const
{
    return mEntity->getName();
}

RigidBody* GameObject::getBody()
{
    return mEntity->getComponent<RigidBody>();
}

void GameObject::checkOnGround(VariantMap& collision)
{
    using namespace EntityCollision;
    
    RigidBody* body = getBody();
    // Should not happen
    if (!body)
        return;
    
    // The contacts data is stored in a slightly malicious way; have to deserialize it from a byte buffer
    const std::vector<unsigned char>& contacts = collision[P_CONTACTS].getBuffer();
    MemoryBuffer contactsBuffer(&contacts[0], contacts.size());
    while (!contactsBuffer.isEof())
    {
        Vector3 contactPosition = contactsBuffer.readVector3();
        Vector3 contactNormal = contactsBuffer.readVector3();
        float contactDepth = contactsBuffer.readFloat();
        float contactVelocity = contactsBuffer.readFloat();
        
        // If contact is below center and mostly vertical, assume it's ground contact
        if (contactPosition.mY < body->getPhysicsPosition().mY)
        {
            float level = fabsf(contactNormal.mY);
            if (level > 0.75f)
                mOnGround = true;
            else
            {
                // If contact is somewhere inbetween vertical/horizontal, the object is sliding a slope
                if (level > 0.1f)
                    mIsSliding = true;
            }
        }
        
        // Ground contact has priority over sliding contact
        if (mOnGround == true)
            mIsSliding = false;
    }
}

Animation* GameObject::getAnim(const std::string& name)
{
    return getResourceCache()->getResource<Animation>(name);
}

Scene* GameObject::getScene() const
{
    return mEntity ? mEntity->getScene() : 0;
}

ResourceCache* GameObject::getResourceCache() const
{
    Scene* scene = getScene();
    if (scene)
        return scene->getResourceCache();
    else
        return 0;
}

void GameObject::handlePhysicsPostStep(StringHash eventType, VariantMap& eventData)
{
    using namespace PhysicsPostStep;
    
    // Check that the scene matches
    Scene* scene = mEntity ? mEntity->getScene() : 0;
    if (eventData[P_SCENE].getPtr() == (void*)scene)
        postUpdateFixed(eventData[P_TIMESTEP].getFloat());
}

void GameObject::handleEntityCollision(StringHash eventType, VariantMap& eventData)
{
    using namespace EntityCollision;
    
    checkOnGround(eventData);
    
    if (!mCanCollide)
        return;
    
    Entity* otherEntity = static_cast<Entity*>(eventData[P_OTHERENTITY].getPtr());
    
    if (otherEntity)
    {
        // Dig out the GameObject
        // If no game object, it's a world collision
        GameObject* other = otherEntity->getDerivedComponent<GameObject>();
        if (!other)
            onCollide(eventData);
        else
        {
            if (other->mCanCollide)
                onCollide(other, eventData);
        }
    }
}

