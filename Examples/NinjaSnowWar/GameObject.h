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

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Component.h"
#include "Controls.h"
#include "EventListener.h"
#include "Quaternion.h"
#include "Scene.h"
#include "SharedPtr.h"
#include "Vector3.h"

#include <string>
#include <vector>

static const int CTRL_UP = 1;
static const int CTRL_DOWN = 2;
static const int CTRL_LEFT = 4;
static const int CTRL_RIGHT = 8;
static const int CTRL_FIRE = 16;
static const int CTRL_JUMP = 32;
static const int CTRL_ALL = 63;

static const int SIDE_UNDEFINED = 0;
static const int SIDE_NEUTRAL = 1;
static const int SIDE_PLAYER = 2;
static const int SIDE_ENEMY = 3;

class Animation;
class Engine;
class Entity;
class EntityCollisionData;
class ResourceCache;
class RigidBody;

class GameObject : public Component, public EventListener
{
    DEFINE_TYPE(GameObject);
    
    friend class Game;
    friend class AIController;
    
public:
    GameObject();
    virtual ~GameObject();
    
    virtual void save(Serializer& dest);
    virtual void load(Deserializer& source, ResourceCache* cache);
    virtual void saveXML(XMLElement& dest);
    virtual void loadXML(const XMLElement& source, ResourceCache* cache);
    virtual bool writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info);
    virtual void readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info);
    
    void create(const Vector3& position = Vector3::sZero, const Quaternion& orientation = Quaternion::sIdentity);
    void setDuration(float duration) { mDuration = duration; }
    void setSide(int side) { mSide = side; }
    void setOrigin(EntityID origin) { mOrigin = origin; }
    void setHealth(int health);
    void setMaxHealth(int maxHealth) { mMaxHealth = maxHealth; }
    void setCanCollide(bool enable);
    
    void postUpdateFixed(float time);
    
    bool damage(int damage, GameObject* source);
    bool heal(int amount);
    template <class T> T* spawnObject(const std::string& name = std::string());
    template <class T> T* createComponent(const std::string& name = std::string());
    void playSound(const std::string& name);
    void playSound(const std::string& name, const Vector3& position);
    
    const std::string& getName() const;
    bool canCollide() const { return mCanCollide; }
    int getSide() const { return mSide; }
    int getHealth() const { return mHealth; }
    int getMaxHealth() const { return mMaxHealth; }
    EntityID getOrigin() const { return mOrigin; }
    EntityID getLastDamageOrigin() const { return mLastDamageOrigin; }
    int getPoints() const { return mPoints; }
    bool isOnGround() const { return mOnGround; }
    bool isSliding() const { return mIsSliding; }
    RigidBody* getBody();
    
    Scene* getScene() const;
    
protected:
    void checkOnGround(VariantMap& collision);
    
    ResourceCache* getResourceCache() const;
    
    virtual void onCreate(const Vector3& position, const Quaternion& orientation) {}
    virtual bool onUpdate(float time) { return true; }
    virtual bool onDamage(int damage) { return true; }
    virtual bool onHeal(int amount) { return false; }
    virtual void onCollide(GameObject* other, VariantMap& collision) {}
    virtual void onCollide(VariantMap& collision) {}
    virtual void onRemove() {}
    
    float mDuration;
    int mSide;
    int mHealth;
    int mMaxHealth;
    bool mOnGround;
    bool mIsSliding;
    bool mCanCollide;
    EntityID mOrigin;
    EntityID mLastDamageOrigin;
    int mPoints;
    
private:
    void handlePhysicsPostStep(StringHash eventType, VariantMap& eventData);
    void handleEntityCollision(StringHash eventType, VariantMap& eventData);
};

template <class T> T* GameObject::spawnObject(const std::string& name)
{
    Entity* newEntity = mEntity->getScene()->createEntity("Obj" + name);
    return newEntity->createComponent<T>();
}

template <class T> T* GameObject::createComponent(const std::string& name)
{
    return mEntity->createComponent<T>(name);
}

#endif // GAMEOBJECT_H
