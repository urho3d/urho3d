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

#ifndef SCENE_ENTITY_H
#define SCENE_ENTITY_H

#include "Component.h"
#include "EventListener.h"
#include "SharedPtr.h"
#include "Variant.h"

#include <set>

#define DEFINE_PROPERTY(propertyID, propertyName) static const ShortStringHash propertyID(#propertyName)

class Scene;

static const EntityID LOCAL_ENTITY = 0x10000;

//! An entity property
struct Property
{
    //! Construct as empty
    Property() :
        mSync(false)
    {
    }
    
    //! Property value
    Variant mValue;
    //! Network replication flag
    bool mSync;
};

//! Map of entity properties
typedef std::map<ShortStringHash, Property> PropertyMap;

//! An object in a scene
class Entity : public RefCounted, public EventListener
{
    friend class Scene;
    
public:
    //! Construct with ID and name
    Entity(EntityID id, const std::string& name = std::string());
    //! Destruct
    virtual ~Entity();
    
    //! Pass event to components who have subscribed to it if any
    virtual void handleEvent(StringHash eventType, VariantMap& eventData);
    //! Write properties and components to a stream
    void save(Serializer& dest);
    //! Read properties and components from a stream
    void load(Deserializer& source, ResourceCache* cache);
    //! Write properties and components to an XML element
    void saveXML(XMLElement& dest);
    //! Read properties and components from an XML element
    void loadXML(const XMLElement& source, ResourceCache* cache);
    //! Let each component resolve component references after loading
    void postLoad(ResourceCache* cache);
    //! Write a network update
    bool writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info);
    //! Let each component resolve component references after a network update
    void postNetUpdate(ResourceCache* cache);
    //! Let each component perform network client-side visual smoothing
    void interpolate(bool snapToEnd = false);
    //! Let each component list component references
    void getComponentRefs(std::vector<ComponentRef>& dest);
    
    //! Set name
    void setName(const std::string& name);
    //! Set network replication flags
    void setNetFlags(unsigned char flags);
    //! Set network owner
    void setOwner(Connection* owner);
    //! Set a property. By default properties are not replicated
    void setProperty(ShortStringHash key, const Variant& value);
    //! Set a property and its replication flag
    void setProperty(ShortStringHash key, const Variant& value, bool sync);
    //! Set replication flag of a property
    void setPropertySync(ShortStringHash key, bool enable);
    //! Set all properties
    void setProperties(const PropertyMap& properties);
    //! Set all properties from a VariantMap and replication flag for all of them
    void setProperties(const VariantMap& properties, bool sync);
    //! Remove a property
    void removeProperty(ShortStringHash key);
    //! Remove all properties
    void removeAllProperties();
    //! Set maximum distance the entity is considered relevant by the server. 0.0 to always be relevant
    void setNetUpdateDistance(float distance);
    //! Set transient client-side prediction timer
    void setPredictionTimer(float time);
    //! Propagate transient client-side prediction timer from another entity
    void setPredictionFrom(Entity* other);
    //! Decrement the transient client-side prediction timer
    void updatePredictionTimer(float timeStep);
    //! Add a component
    void addComponent(Component* component);
    //! Create a component with specified type and name. Throw an exception if no factory can create.
    Component* createComponent(ShortStringHash type, const std::string& name = std::string());
    //! Remove a component
    void removeComponent(Component* component);
    //! Remove a component by type and name
    void removeComponent(ShortStringHash type, const std::string& name = std::string());
    //! Remove a component by type and name hash
    void removeComponent(ShortStringHash type, StringHash nameHash);
    //! Remove all components
    void removeAllComponents();
    //! Template version of creating a component. Throw an exception if no factory can create.
    template <class T> T* createComponent(const std::string& name = std::string());
    //! Template version of removing a component by name
    template <class T> void removeComponent(const std::string& name = std::string());
    //! Template version of removing a component by name hash
    template <class T> void removeComponent(StringHash nameHash);
    
    //! Return entity ID
    EntityID getID() const { return mID; }
    //! Return whether entity is local
    bool isLocal() const { return (mID >= LOCAL_ENTITY) != 0; }
    //! Return name
    const std::string& getName() const { return mName; }
    //! Return name hash
    StringHash getNameHash() const { return mNameHash; }
    //! Return network replication flags
    unsigned char getNetFlags() const { return mNetFlags; }
    //! Return scene
    Scene* getScene() const { return mScene; }
    //! Return network owner
    Connection* getOwner() const { return mOwner; }
    //! Return whether has a property
    bool hasProperty(ShortStringHash key) const;
    //! Return a property
    const Variant& getProperty(ShortStringHash key) const;
    //! Return replication flag for a property
    bool getPropertySync(ShortStringHash key) const;
    //! Return all properties
    const PropertyMap& getProperties() const { return mProperties; }
    //! Return maximum distance for network updates
    float getNetUpdateDistance() const { return mNetUpdateDistance; }
    //! Return transient client-side prediction timer
    float getPredictionTimer() const { return mPredictionTimer; }
    //! Return unique one-letter component name
    std::string getUniqueComponentName();
    //! Return whether has a component of specific type. Name is not checked
    bool hasComponent(ShortStringHash type) const;
    //! Return whether has a component with specific type and name
    bool hasComponent(ShortStringHash type, const std::string& name) const;
    //! Return whether has a component with specific type and name hash
    bool hasComponent(ShortStringHash type, StringHash nameHash) const;
    //! Return whether has a component by combined 16-bit hash
    bool hasComponent(unsigned short combinedHash) const;
    //! Return the first component of a specific type, null if not found
    Component* getComponent(ShortStringHash type) const;
    //! Return a component with specific type and name, null if not found
    Component* getComponent(ShortStringHash type, const std::string& name) const;
    //! Return a component with specific type and name hash, null if not found
    Component* getComponent(ShortStringHash type, StringHash nameHash) const;
    //! Return a component by combined 16-bit hash, null if not found
    Component* getComponent(unsigned short combinedHash) const;
    //! Return all components
    const std::vector<SharedPtr<Component> >& getComponents() const { return mComponents; }
    //! Return components of a specific type
    std::vector<Component*> getComponents(ShortStringHash type) const;
    //! Return whether is in a server scene
    bool isAuthority() const { return (mNetFlags & NET_AUTHORITY) != 0; }
    //! Return whether is in a client scene
    bool isProxy() const { return (mNetFlags & NET_PROXY) != 0; }
    //! Return whether is client-side predicted by the owner
    bool isOwnerPredicted() const { return (mNetFlags & NET_OWNERPREDICT) != 0; }
    //! Return whether can be transiently client-side predicted
    bool isTransientPredicted() const { return (mNetFlags & NET_TRANSIENTPREDICT) != 0; }
    //! Return whether scene is performing client-side prediction by replaying controls
    bool isPlayback() const;
    //! Return whether entity should be replicated to the connection
    bool checkSync(Connection* connection) const;
    //! Return whether should do client-side prediction on the entity
    bool checkPrediction(Connection* connection = 0) const;
    
    //! Template version of checking for component
    template <class T> bool hasComponent() const;
    //! Template version of checking for component by name
    template <class T> bool hasComponent(const std::string& name) const;
    //! Template version of checking for component by name hash
    template <class T> bool hasComponent(StringHash nameHash) const;
    //! Template version of returning first component of specific type
    template <class T> T* getComponent() const;
    //! Template version of returning a component by name
    template <class T> T* getComponent(const std::string& name) const;
    //! Template version of returning a component by name hash
    template <class T> T* getComponent(StringHash nameHash) const;
    //! Return whether has a component derived from class
    template <class T> bool hasDerivedComponent() const;
    //! Return whether has a component derived from class with specific name
    template <class T> bool hasDerivedComponent(const std::string& name) const;
    //! Return whether has a component derived from class with specific name hash
    template <class T> bool hasDerivedComponent(StringHash nameHash) const;
    //! Return first component derived from class
    template <class T> T* getDerivedComponent() const;
    //! Return component derived from class with specific name
    template <class T> T* getDerivedComponent(const std::string& name) const;
    //! Return component derived from class with specific name hash
    template <class T> T* getDerivedComponent(StringHash nameHash) const;
    //! Template version of returning components of specific type
    template <class T> std::vector<T*> getComponents() const;
    //! Return all components derived from class
    template <class T> std::vector<T*> getDerivedComponents() const;
    
private:
    //! Remove a component by iterator
    void removeComponent(std::vector<SharedPtr<Component> >::iterator i, bool removeAll = false);
    //! Check which components are event listeners
    void updateEventListeners();
    
    //! ID
    EntityID mID;
    //! Name
    std::string mName;
    //! Name hash
    StringHash mNameHash;
    //! Network replication flags
    unsigned char mNetFlags;
    //! Scene
    Scene* mScene;
    //! Network owner
    Connection* mOwner;
    //! Components
    std::vector<SharedPtr<Component> > mComponents;
    //! Components that are event listeners
    std::vector<EventListener*> mEventListeners;
    //! Properties
    PropertyMap mProperties;
    //! Next unique component name
    unsigned char mNextComponentName;
    //! Maximum network update distance
    float mNetUpdateDistance;
    //! Transient client-side prediction timer
    float mPredictionTimer;
};

template <class T> T* Entity::createComponent(const std::string& name)
{
    return static_cast<T*>(createComponent(T::getTypeStatic(), name));
}

template <class T> void Entity::removeComponent(const std::string& name)
{
    ShortStringHash type = T::getTypeStatic();
    removeComponent(type, name);
}

template <class T> void Entity::removeComponent(StringHash nameHash)
{
    ShortStringHash type = T::getTypeStatic();
    removeComponent(type, nameHash);
}

template <class T> bool Entity::hasComponent() const
{
    ShortStringHash type = T::getTypeStatic();
    return hasComponent(type);
}

template <class T> bool Entity::hasComponent(const std::string& name) const
{
    ShortStringHash type = T::getTypeStatic();
    return hasComponent(type, name);
}

template <class T> bool Entity::hasComponent(StringHash nameHash) const
{
    ShortStringHash type = T::getTypeStatic();
    return hasComponent(type, nameHash);
}

template <class T> T* Entity::getComponent() const
{
    ShortStringHash type = T::getTypeStatic();
    return static_cast<T*>(getComponent(type));
}

template <class T> T* Entity::getComponent(const std::string& name) const
{
    ShortStringHash type = T::getTypeStatic();
    return static_cast<T*>(getComponent(type, name));
}

template <class T> T* Entity::getComponent(StringHash nameHash) const
{
    ShortStringHash type = T::getTypeStatic();
    return static_cast<T*>(getComponent(type, nameHash));
}

template <class T> bool Entity::hasDerivedComponent() const
{
    for (std::vector<SharedPtr<Component> >::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        T* ptr = dynamic_cast<T*>(i->getPtr());
        if (ptr)
            return true;
    }
    
    return false;
}

template <class T> bool Entity::hasDerivedComponent(const std::string& name) const
{
    for (std::vector<SharedPtr<Component> >::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if ((*i)->getName() == name)
        {
            T* ptr = dynamic_cast<T*>(i->getPtr());
            if (ptr)
                return true;
        }
    }
    
    return false;
}

template <class T> bool Entity::hasDerivedComponent(StringHash nameHash) const
{
    for (std::vector<SharedPtr<Component> >::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if ((*i)->getNameHash() == nameHash)
        {
            T* ptr = dynamic_cast<T*>(i->getPtr());
            if (ptr)
                return true;
        }
    }
    
    return false;
}

template <class T> T* Entity::getDerivedComponent() const
{
    ShortStringHash type = T::getTypeStatic();
    
    for (std::vector<SharedPtr<Component> >::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        T* ptr = dynamic_cast<T*>(i->getPtr());
        if (ptr)
            return ptr;
    }
    
    return 0;
}

template <class T> T* Entity::getDerivedComponent(const std::string& name) const
{
    ShortStringHash type = T::getTypeStatic();
    
    for (std::vector<SharedPtr<Component> >::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if ((*i)->getName() == name)
        {
            T* ptr = dynamic_cast<T*>(i->getPtr());
            if (ptr)
                return ptr;
        }
    }
    
    return 0;
}

template <class T> T* Entity::getDerivedComponent(StringHash nameHash) const
{
    StringHash type = T::getTypeStatic();
    
    for (std::vector<SharedPtr<Component> >::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if ((*i)->getNameHash() == nameHash)
        {
            T* ptr = dynamic_cast<T*>(i->getPtr());
            if (ptr)
                return ptr;
        }
    }
    
    return 0;
}

template <class T> std::vector<T*> Entity::getComponents() const
{
    std::vector<T*> components;
    ShortStringHash type = T::getTypeStatic();
    
    for (std::vector<SharedPtr<Component> >::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if ((*i)->getType() == type)
            components.push_back(static_cast<T*>(i->getPtr()));
    }
    
    return components;
}

template <class T> std::vector<T*> Entity::getDerivedComponents() const
{
    std::vector<T*> components;
    
    std::vector<SharedPtr<Component> >::const_iterator i = mComponents.begin();
    while (i != mComponents.end())
    {
        T* ptr = dynamic_cast<T*>(i->getPtr());
        if (ptr)
            components.push_back(ptr);
        ++i;
    }
    
    return components;
}

#endif // SCENE_ENTITY_H
