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
#include "Log.h"
#include "Scene.h"
#include "StringUtils.h"

#include "DebugNew.h"

Entity::Entity(EntityID id, const std::string& name) :
    mID(id),
    mName(name),
    mNameHash(name),
    mNetFlags(NET_SYNCTOALL),
    mGroupFlags(0),
    mScene(0),
    mOwner(0),
    mNextComponentName(0x30),
    mNetUpdateDistance(0.0f),
    mPredictionTimer(0.0f)
{
}

Entity::~Entity()
{
    removeAllComponents();
}

void Entity::onEvent(EventListener* sender, StringHash eventType, VariantMap& eventData)
{
    WeakPtr<Entity> self(this);
    
    // Special-case event handling: send to all components that are event listeners
    for (unsigned i = 0; i < mEventListeners.size(); ++i)
    {
        // Do not check if the component actually subscribes to the event, because its onEvent() does that check
        mEventListeners[i]->onEvent(sender, eventType, eventData);
        
        // Exit immediately if entity was removed as a response to the event
        if (self.isExpired())
            return;
    }
}

void Entity::save(Serializer& dest)
{
    // Write identification and flags
    dest.writeUInt(mID);
    dest.writeString(mName);
    dest.writeUByte(mNetFlags);
    dest.writeFloat(mNetUpdateDistance);
    dest.writeUInt(mGroupFlags);
    
    // Write properties
    dest.writeVLE(mProperties.size());
    for (PropertyMap::const_iterator i = mProperties.begin(); i != mProperties.end(); ++i)
    {
        dest.writeShortStringHash(i->first);
        dest.writeVariant(i->second.mValue);
        dest.writeBool(i->second.mSync);
    }
    
    // Write components
    dest.writeVLE(mComponents.size());
    for (std::vector<SharedPtr<Component> >::iterator i = mComponents.begin(); i != mComponents.end(); ++i)
        (*i)->save(dest);
}

void Entity::load(Deserializer& source, ResourceCache* cache)
{
    // Load should only be called for new entities, but remove components just to be sure
    removeAllComponents();
    
    // Scene reads the identification, so do not read here
    mNetFlags = source.readUByte();
    mNetUpdateDistance = source.readFloat();
    mGroupFlags = source.readUInt();
    
    // Read properties
    mProperties.clear();
    unsigned numProperties = source.readVLE();
    for (unsigned i = 0; i < numProperties; ++i)
    {
        ShortStringHash key = source.readShortStringHash();
        Property newProperty;
        newProperty.mValue = source.readVariant();
        newProperty.mSync = source.readBool();
        mProperties[key] = newProperty;
    }
    
    // Create and read components
    unsigned numComponents = source.readVLE();
    for (unsigned i = 0; i < numComponents; ++i)
    {
        ShortStringHash type = source.readShortStringHash();
        std::string name = source.readString();
        Component* newComponent = createComponent(type, name);
        newComponent->load(source, cache);
    }
}

void Entity::saveXML(XMLElement& dest)
{
    // Write identification and flags
    dest.setInt("id", mID);
    if (!mName.empty())
        dest.setString("name", mName);
    dest.setInt("netflags", mNetFlags);
    dest.setFloat("netdistance", mNetUpdateDistance);
    dest.setInt("groupflags", mGroupFlags);
    
    // Write properties
    for (PropertyMap::const_iterator i = mProperties.begin(); i != mProperties.end(); ++i)
    {
        XMLElement propertyElem = dest.createChildElement("property");
        // Use name if possible, or hash if reverse mapping is unavailable
        std::string name = shortHashToString(i->first);
        if (name.empty())
            propertyElem.setInt("hash", i->first.mData);
        else
            propertyElem.setString("name", name);
        propertyElem.setVariant(i->second.mValue);
        propertyElem.setBool("sync", i->second.mSync);
    }
    
    // Write components
    for (std::vector<SharedPtr<Component> >::iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        XMLElement componentElem = dest.createChildElement("component");
        (*i)->saveXML(componentElem);
    }
}

void Entity::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Load should only be called for new entities, but remove components just to be sure
    removeAllComponents();
    
    // Scene reads the identification, so do not read here
    mNetFlags = source.getInt("netflags");
    mNetUpdateDistance = source.getFloat("netdistance");
    mGroupFlags = source.getInt("groupflags");
    
    // Read properties
    mProperties.clear();
    XMLElement propertyElem = source.getChildElement("property");
    while (propertyElem)
    {
        ShortStringHash key;
        if (propertyElem.hasAttribute("hash"))
            key.mData = propertyElem.getInt("hash");
        else
            key = ShortStringHash(propertyElem.getString("name"));
        Property newProperty;
        newProperty.mValue = propertyElem.getVariant();
        newProperty.mSync = propertyElem.getBool("sync");
        mProperties[key] = newProperty;
        propertyElem = propertyElem.getNextElement("property");
    }
    
    // Create and read components
    XMLElement componentElem = source.getChildElement("component");
    while (componentElem)
    {
        std::string type = componentElem.getString("type");
        std::string name = componentElem.getString("name");
        Component* newComponent = createComponent(ShortStringHash(type), name);
        newComponent->loadXML(componentElem, cache);
        componentElem = componentElem.getNextElement("component");
    }
}

void Entity::postLoad(ResourceCache* cache)
{
    // Perform post-load on all components (resolve entity & component references)
    for (std::vector<SharedPtr<Component> >::iterator i = mComponents.begin(); i != mComponents.end(); ++i)
        (*i)->postLoad(cache);
}

bool Entity::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    // Note: this function only builds a delta-update of entity properties, not components
    VariantMap baseProperties;
    if (baseRevision.getSize())
    {
        // We read the base properties as an ordinary variantmap, because only synced properties are stored,
        // and therefored storing the sync bool would be redundant
        baseProperties = baseRevision.readVariantMap();
    }
    
    unsigned syncedProperties = 0;
    std::set<ShortStringHash> changedProperties;
    
    for (PropertyMap::iterator i = mProperties.begin(); i != mProperties.end(); ++i)
    {
        if (i->second.mSync)
        {
            VariantMap::const_iterator j = baseProperties.find(i->first);
            if ((j == baseProperties.end()) || (i->second.mValue != j->second))
                changedProperties.insert(i->first);
            ++syncedProperties;
        }
    }
    
    // Write all synced properties to the dest.revision buffer, and delta to network stream
    destRevision.writeVLE(syncedProperties);
    dest.writeVLE(changedProperties.size());
    for (PropertyMap::iterator i = mProperties.begin(); i != mProperties.end(); ++i)
    {
        if (i->second.mSync)
        {
            destRevision.writeShortStringHash(i->first);
            destRevision.writeVariant(i->second.mValue);
            if (changedProperties.find(i->first) != changedProperties.end())
            {
                dest.writeShortStringHash(i->first);
                dest.writeVariant(i->second.mValue);
            }
        }
    }
    
    return changedProperties.size() > 0;
}

void Entity::postNetUpdate(ResourceCache* cache)
{
    // Perform post-network update on all components (resolve entity & component references)
    // Note: does not track which components actually got updated. For most components this is a no-op
    for (std::vector<SharedPtr<Component> >::iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if ((*i)->isProxy())
            (*i)->postNetUpdate(cache);
    }
}

void Entity::interpolate(bool snapToEnd)
{
    // Interpolate all proxy components
    for (std::vector<SharedPtr<Component> >::iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if ((*i)->isProxy())
            (*i)->interpolate(snapToEnd);
    }
}

void Entity::getComponentRefs(std::vector<ComponentRef>& dest)
{
    dest.clear();
    for (std::vector<SharedPtr<Component> >::iterator i = mComponents.begin(); i != mComponents.end(); ++i)
        (*i)->getComponentRefs(dest);
}

void Entity::getResourceRefs(std::vector<Resource*>& dest)
{
    dest.clear();
    for (std::vector<SharedPtr<Component> >::iterator i = mComponents.begin(); i != mComponents.end(); ++i)
        (*i)->getResourceRefs(dest);
}

void Entity::setName(const std::string& name)
{
    mName = name;
    mNameHash = StringHash(name);
}

void Entity::setNetFlags(unsigned char flags)
{
    // Respect the authority and proxy flags if they have been set already
    if (mNetFlags & NET_MODEFLAGS)
        mNetFlags = (mNetFlags & NET_MODEFLAGS) | (flags & ~NET_MODEFLAGS);
    else
        mNetFlags = flags;
}

void Entity::setGroupFlags(unsigned flags)
{
    mGroupFlags = flags;
}

void Entity::setOwner(Connection* owner)
{
    if (mID >= LOCAL_ENTITY)
    {
        LOGERROR("Owner can not be set for local entities");
        return;
    }
    
    mOwner = owner;
}

void Entity::setProperty(ShortStringHash key, const Variant& value)
{
    mProperties[key].mValue = value;
}

void Entity::setProperty(ShortStringHash key, const Variant& value, bool sync)
{
    mProperties[key].mValue = value;
    mProperties[key].mSync = sync;
}

void Entity::setPropertySync(ShortStringHash key, bool enable)
{
    mProperties[key].mSync = enable;
}

void Entity::setProperties(const PropertyMap& properties)
{
    mProperties = properties;
}

void Entity::setProperties(const VariantMap& properties, bool sync)
{
    mProperties.clear();
    for (VariantMap::const_iterator i = properties.begin(); i != properties.end(); ++i)
    {
        Property newProperty;
        newProperty.mValue = i->second;
        newProperty.mSync = sync;
        mProperties[i->first] = newProperty;
    }
}

void Entity::setNetUpdateDistance(float distance)
{
    mNetUpdateDistance = max(distance, 0.0f);
}

void Entity::setPredictionTimer(float time)
{
    if (!isTransientPredicted())
        return;
    
    mPredictionTimer = time;
}

void Entity::setPredictionFrom(Entity* other)
{
    if (!isTransientPredicted())
        return;
    
    // If the other entity is owner-predicted, set full prediction period. Otherwise propagate the higher timer value
    if (other->isOwnerPredicted())
        mPredictionTimer = mScene->getTransientPredictionTime();
    if (other->isTransientPredicted())
        mPredictionTimer = max(mPredictionTimer, other->getPredictionTimer());
}

void Entity::updatePredictionTimer(float timeStep)
{
    // Decrement prediction timer if necessary
    if (mPredictionTimer > 0.0f)
        mPredictionTimer = max(mPredictionTimer - timeStep, 0.0f);
}

void Entity::removeProperty(ShortStringHash key)
{
    PropertyMap::iterator i = mProperties.find(key);
    if (i != mProperties.end())
        mProperties.erase(i);
}

void Entity::removeAllProperties()
{
    mProperties.clear();
}

void Entity::addComponent(Component* component)
{
    if (!component)
    {
        LOGERROR("Null component for addComponent");
        return;
    }
    
    ShortStringHash combinedHash = component->getCombinedHash();
    
    for (std::vector<SharedPtr<Component> >::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        // Make sure component is not already added
        if (component == *i)
        {
            LOGWARNING("Component " + component->getTypeName() + " already added to entity " + mName);
            return;
        }
        // Check the same combined hash does not already exist (can not replicate or load/save parent references)
        if (combinedHash == (*i)->getCombinedHash())
        {
            // If types differ, it is a more insiduous hash collision
            if (component->getType() != (*i)->getType())
            {
                SAFE_EXCEPTION("Component hash collision between " + component->getTypeName() + " name " + component->getName() +
                    " and " + (*i)->getTypeName() + " name " + (*i)->getName() + " in entity " + mName);
            }
            // The more common cause is adding several components with the same type and name
            else
            {
                LOGWARNING("Component with type " + component->getTypeName() + " name " + component->getName() +
                    " already exists in entity " + mName);
            }
        }
    }
    
    component->mEntity = this;
    mComponents.push_back(SharedPtr<Component>(component));
    
    updateEventListeners();
}

Component* Entity::createComponent(ShortStringHash type, const std::string& name)
{
    if (!mScene)
        EXCEPTION("Entity not in scene, can not create components");
    
    SharedPtr<Component> newComponent = mScene->createComponent(type, name);
    addComponent(newComponent);
    return newComponent;
}

void Entity::removeComponent(Component* component)
{
    if (!component)
        return;
    
    for (std::vector<SharedPtr<Component> >::iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if ((*i) == component)
        {
            removeComponent(i);
            return;
        }
    }
    
    LOGWARNING("Component " + component->getTypeName() + " not found in entity " + mName);
}

void Entity::removeComponent(ShortStringHash type, const std::string& name)
{
    for (std::vector<SharedPtr<Component> >::iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if (((*i)->getType() == type) && ((name.empty()) || ((*i)->getName() == name)))
        {
            removeComponent(i);
            return;
        }
    }
    
    LOGWARNING("Component type " + toString(type) + " name " + name + " not found in entity " + mName);
}

void Entity::removeComponent(ShortStringHash type, StringHash nameHash)
{
    for (std::vector<SharedPtr<Component> >::iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if (((*i)->getType() == type) && ((!nameHash) || ((*i)->getNameHash() == nameHash)))
        {
            removeComponent(i);
            return;
        }
    }
    
    LOGWARNING("Component type " + toString(type) + " name hash " + toString(nameHash) + " not found in entity " + mName);
}

void Entity::removeAllComponents()
{
    while (mComponents.size())
        removeComponent(mComponents.end() - 1, true);
    
    mEventListeners.clear();
}

bool Entity::hasProperty(ShortStringHash key) const
{
    PropertyMap::const_iterator i = mProperties.find(key);
    if (i == mProperties.end())
        return false;
    return i->second.mValue.getType() != VAR_NONE;
}

const Variant& Entity::getProperty(ShortStringHash key) const
{
    static const Variant empty;
    
    PropertyMap::const_iterator i = mProperties.find(key);
    if (i == mProperties.end())
        return empty;
    else
        return i->second.mValue;
}

bool Entity::getPropertySync(ShortStringHash key) const
{
    PropertyMap::const_iterator i = mProperties.find(key);
    if (i == mProperties.end())
        return false;
    else
        return i->second.mSync;
}

std::string Entity::getUniqueComponentName()
{
    std::string ret;
    ret += mNextComponentName;
    
    ++mNextComponentName;
    // Use only 0-9, @-Z and a-z to be sure component survives XML serialization
    if (mNextComponentName == 0x3a)
        mNextComponentName = 0x40;
    if (mNextComponentName == 0x5b)
        mNextComponentName = 0x61;
    if (mNextComponentName == 0x7b)
        mNextComponentName = 0x30;
    
    return ret;
}

bool Entity::hasComponent(ShortStringHash type) const
{
    for (std::vector<SharedPtr<Component> >::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if ((*i)->getType() == type)
            return true;
    }
    
    return false;
}

bool Entity::hasComponent(ShortStringHash type, const std::string& name) const
{
    for (std::vector<SharedPtr<Component> >::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if (((*i)->getType() == type) && ((*i)->getName() == name))
            return true;
    }
    
    return false;
}

bool Entity::hasComponent(ShortStringHash type, StringHash nameHash) const
{
    for (std::vector<SharedPtr<Component> >::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if (((*i)->getType() == type) && ((*i)->getNameHash() == nameHash))
            return true;
    }
    
    return false;
}

bool Entity::hasComponent(unsigned short combinedHash) const
{
    for (std::vector<SharedPtr<Component> >::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if ((*i)->getCombinedHash().mData == combinedHash)
            return true;
    }
    
    return false;
}

Component* Entity::getComponent(ShortStringHash type) const
{
    for (std::vector<SharedPtr<Component> >::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if ((*i)->getType() == type)
            return *i;
    }
    
    return 0;
}

Component* Entity::getComponent(ShortStringHash type, const std::string& name) const
{
    for (std::vector<SharedPtr<Component> >::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if (((*i)->getType() == type) && ((*i)->getName() == name))
            return *i;
    }
    
    return 0;
}

Component* Entity::getComponent(ShortStringHash type, StringHash nameHash) const
{
    for (std::vector<SharedPtr<Component> >::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if (((*i)->getType() == type) && ((*i)->getNameHash() == nameHash))
            return *i;
    }
    
    return 0;
}

Component* Entity::getComponent(unsigned short combinedHash) const
{
    for (std::vector<SharedPtr<Component> >::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if ((*i)->getCombinedHash().mData == combinedHash)
            return *i;
    }
    
    return 0;
}

void Entity::getComponents(std::vector<Component*>& result, ShortStringHash type) const
{
    result.clear();
    for (std::vector<SharedPtr<Component> >::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if ((*i)->getType() == type)
            result.push_back(*i);
    }
}

bool Entity::isPlayback() const
{
    if (!mScene)
        return false;
    return mScene->isPlayback();
}

bool Entity::checkSync(Connection* connection) const
{
    if (mNetFlags & NET_SYNCTONONE)
        return false;
    
    if (mNetFlags & NET_SYNCTOOWNER)
        return mOwner == connection;
    
    return true;
}

bool Entity::checkPrediction(Connection* connection) const
{
    if (isOwnerPredicted())
    {
        // On server need to check the actual owner. On client need only check if owner is non-null
        if (isAuthority())
        {
            if ((mOwner) && (mOwner == connection))
                return true;
        }
        else
        {
            if (mOwner)
                return true;
        }
    }
    
    if (isTransientPredicted())
        return mPredictionTimer > 0.0f;
    
    return false;
}

void Entity::removeComponent(std::vector<SharedPtr<Component> >::iterator i, bool removeAll)
{
    (*i)->mEntity = 0;
    mComponents.erase(i);
    
    if (!removeAll)
        updateEventListeners();
}

void Entity::updateEventListeners()
{
    mEventListeners.clear();
    
    for (std::vector<SharedPtr<Component> >::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        EventListener* listener = dynamic_cast<EventListener*>(i->getPtr());
        if (listener)
            mEventListeners.push_back(listener);
    }
}
