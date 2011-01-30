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
#include "ComponentFactory.h"
#include "Log.h"
#include "Node.h"
#include "PackageFile.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "SceneExtension.h"
#include "StringUtils.h"
#include "XMLFile.h"

#include "DebugNew.h"

static const int ASYNC_MIN_FPS = 50;

Scene::Scene(ResourceCache* cache, const std::string& name) :
    mCache(cache),
    mName(name),
    mNameHash(name),
    mNextEntityID(1),
    mNextLocalEntityID(LOCAL_ENTITY),
    mNetFlags(NET_NONE),
    mChecksum(0),
    mTransientPredictionTime(2.0f),
    mInterpolationConstant(50.0f),
    mInterpolationSnapThreshold(1.0f),
    mInterpolationLerpFactor(1.0f),
    mPlayback(false),
    mAsyncLoading(false)
{
    LOGINFO("Scene " + mName + " created");
}

Scene::~Scene()
{
    removeAllEntities();
    
    LOGINFO("Scene " + mName + " destroyed");
}

void Scene::update(float timeStep)
{
    // If loading in progress, update it instead
    if (mAsyncLoading)
    {
        updateAsyncLoading();
        return;
    }
    
    PROFILE(Scene_Update);
    
    using namespace SceneUpdate;
    
    // Send update event
    VariantMap sceneUpdateData;
    sceneUpdateData[P_SCENE] = this;
    sceneUpdateData[P_TIMESTEP] = timeStep;
    sendEvent(EVENT_SCENEUPDATE, sceneUpdateData);
    
    // Update delayed events & delayed remote events
    processDelayedEvents(timeStep);
    processRemoteEvents(timeStep);
    
    // Update extensions
    for (std::map<ShortStringHash, SharedPtr<SceneExtension> >::iterator i = mExtensions.begin(); i != mExtensions.end(); ++i)
        i->second->update(timeStep);
    
    // Send post-update event
    sendEvent(EVENT_SCENEPOSTUPDATE, sceneUpdateData);
    
    // In networked client scenes, interpolate entities and update transient prediction timers
    if ((!isPlayback()) && (isProxy()))
        interpolate(timeStep);
}

void Scene::interpolate(float timeStep)
{
    PROFILE(Scene_Interpolate);
    
    mInterpolationLerpFactor = 1.0f - clamp(powf(2.0f, -timeStep * mInterpolationConstant), 0.0f, 1.0f);
    
    for (std::map<EntityID, SharedPtr<Entity> >::iterator i = mEntities.begin(); i != mEntities.end(); ++i)
    {
        // Stop when local entity ID range reached
        if (i->first >= LOCAL_ENTITY)
            break;
        
        i->second->interpolate();
        i->second->updatePredictionTimer(timeStep);
    }
}

void Scene::save(Serializer& dest)
{
    // Write scene name
    dest.writeString(mName);
    
    // Write extension properties
    saveProperties(dest);
    
    // Write entities
    dest.writeUInt(mEntities.size());
    for (std::map<EntityID, SharedPtr<Entity> >::iterator i = mEntities.begin(); i != mEntities.end(); ++i)
    {
        // Create a separate serialization buffer for the entity, in case something fails
        Entity* entity = i->second;
        VectorBuffer entityBuffer;
        
        try
        {
            entity->save(entityBuffer);
            dest.writeVLE(entityBuffer.getSize());
            dest.write(entityBuffer.getData(), entityBuffer.getSize());
        }
        catch (...)
        {
            // Something went wrong. Save a zero length buffer
            LOGERROR("Failed to save entity " + toString(entity->getID()));
            dest.writeVLE(0);
        }
    }
}

void Scene::load(Deserializer& source)
{
    if (!mCache)
        return;
    
    LOGINFO("Loading scene from " + source.getName());
    
    stopAsyncLoading();
    removeAllEntities();
    
    // Read scene name
    mName = source.readString();
    
    // Read extension properties
    loadProperties(source);
    
    // Read entities
    unsigned numEntities = source.readUInt();
    for (unsigned i = 0; i < numEntities; ++i)
        loadEntity(source);
    
    finishLoading(source);
}

void Scene::saveXML(Serializer& dest)
{
    XMLFile xml;
    XMLElement sceneElem = xml.createRootElement("scene");
    
    // Write scene name
    if (!mName.empty())
        sceneElem.setString("name", mName);
    
    // Write extension properties
    savePropertiesXML(sceneElem);
    
    // Write entities
    for (std::map<EntityID, SharedPtr<Entity> >::iterator i = mEntities.begin(); i != mEntities.end(); ++i)
    {
        Entity* entity = i->second;
        XMLElement entityElem = sceneElem.createChildElement("entity");
        
        try
        {
            entity->saveXML(entityElem);
        }
        catch (...)
        {
            // Something went wrong. Remove the element
            sceneElem.removeChildElement("entity");
            LOGERROR("Failed to save entity " + toString(entity->getID()));
        }
    }
    
    xml.save(dest);
}

void Scene::loadXML(Deserializer& source)
{
    if (!mCache)
        return;
    
    LOGINFO("Loading XML scene from " + source.getName());
    
    XMLFile xml;
    xml.load(source, mCache);
    XMLElement sceneElem = xml.getRootElement();
    
    stopAsyncLoading();
    removeAllEntities();
    
    // Read scene name
    mName = sceneElem.getString("name");
    
    // Read extension properties
    loadPropertiesXML(sceneElem);
    
    // Read entities
    XMLElement entityElem = sceneElem.getChildElement("entity");
    while (entityElem)
        loadEntityXML(entityElem);
    
    finishLoading(source);
}

void Scene::saveProperties(Serializer& dest)
{
    // Write network interpolation properties
    dest.writeFloat(mTransientPredictionTime);
    dest.writeFloat(mInterpolationConstant);
    dest.writeFloat(mInterpolationSnapThreshold);
    
    // Write extension properties
    for (std::map<ShortStringHash, SharedPtr<SceneExtension> >::iterator i = mExtensions.begin(); i != mExtensions.end(); ++i)
        i->second->save(dest);
}

void Scene::loadProperties(Deserializer& source)
{
    if (!mEntities.empty())
        EXCEPTION("Scene must be empty when loading properties");
    
    // Read network interpolation properties
    mTransientPredictionTime = source.readFloat();
    mInterpolationConstant = source.readFloat();
    mInterpolationSnapThreshold = source.readFloat();
    
    // Read extension properties
    for (std::map<ShortStringHash, SharedPtr<SceneExtension> >::iterator i = mExtensions.begin(); i != mExtensions.end(); ++i)
        i->second->load(source);
}

void Scene::savePropertiesXML(XMLElement& dest)
{
    // Write network interpolation properties
    XMLElement interpolationElem = dest.createChildElement("interpolation");
    interpolationElem.setFloat("predictiontime", mTransientPredictionTime);
    interpolationElem.setFloat("constant", mInterpolationConstant);
    interpolationElem.setFloat("snapthreshold", getInterpolationSnapThreshold());
    
    // Write extension properties
     for (std::map<ShortStringHash, SharedPtr<SceneExtension> >::iterator i = mExtensions.begin(); i != mExtensions.end(); ++i)
        i->second->saveXML(dest);
}

void Scene::loadPropertiesXML(const XMLElement& source)
{
    if (!mEntities.empty())
        EXCEPTION("Scene must be empty when loading properties");
    
    // Read network interpolation properties
    if (source.hasChildElement("interpolation"))
    {
        XMLElement interpolationElem = source.getChildElement("interpolation");
        mTransientPredictionTime = interpolationElem.getFloat("predictiontime");
        mInterpolationConstant = interpolationElem.getFloat("constant");
        setInterpolationSnapThreshold(interpolationElem.getFloat("snapthreshold"));
    }
    
    // Read extension properties
    for (std::map<ShortStringHash, SharedPtr<SceneExtension> >::iterator i = mExtensions.begin(); i != mExtensions.end(); ++i)
        i->second->loadXML(source);
}

void Scene::storePredictedEntities()
{
    if (mAsyncLoading)
        return;
    
    PROFILE(Scene_StorePredictedEntities);
    
    mPredictedEntityData.clear();
    
    for (std::map<EntityID, SharedPtr<Entity> >::iterator i = mEntities.begin(); i != mEntities.end(); ++i)
    {
        // Local entities should not be affected by prediction, so stop when local entity ID range reached
        if (i->first >= LOCAL_ENTITY)
            break;
        
        Entity* entity = i->second;
        if (entity->checkPrediction())
        {
            // Prepare a separate vector buffer for the entity
            VectorBuffer entityBuffer;
            entityBuffer.writeUShort(entity->getID());
            
            // Write properties
            const PropertyMap& properties = entity->getProperties();
            entityBuffer.writeVLE(properties.size());
            for (PropertyMap::const_iterator j = properties.begin(); j != properties.end(); ++j)
            {
                entityBuffer.writeShortStringHash(j->first);
                entityBuffer.writeVariant(j->second.mValue);
                entityBuffer.writeBool(j->second.mSync);
            }
            
            // Write components
            const std::vector<SharedPtr<Component> >& components = entity->getComponents();
            for (std::vector<SharedPtr<Component> >::const_iterator j = components.begin(); j != components.end(); ++j)
            {
                Component* component = *j;
                if (component->checkPrediction())
                {
                    VectorBuffer componentBuffer;
                    component->save(componentBuffer);
                    entityBuffer.writeVLE(componentBuffer.getSize());
                    entityBuffer.write(componentBuffer.getData(), componentBuffer.getSize());
                }
            }
            
            mPredictedEntityData.writeVLE(entityBuffer.getSize());
            mPredictedEntityData.write(entityBuffer.getData(), entityBuffer.getSize());
        }
    }
}

void Scene::restorePredictedEntities()
{
    if (mAsyncLoading)
        return;
    
    PROFILE(Scene_RestorePredictedEntities);
    
    mPredictedEntityData.seek(0);
    
    try
    {
        while (!mPredictedEntityData.isEof())
        {
            unsigned entityDataSize = mPredictedEntityData.readVLE();
            if (entityDataSize)
            {
                VectorBuffer entityBuffer(mPredictedEntityData, entityDataSize);
                EntityID id = entityBuffer.readUShort();
                Entity* entity = getEntity(id);
                if (entity)
                {
                    // Read properties
                    PropertyMap properties;
                    unsigned numProperties = entityBuffer.readVLE();
                    for (unsigned i = 0; i < numProperties; ++i)
                    {
                        ShortStringHash key = entityBuffer.readShortStringHash();
                        Property newProperty;
                        newProperty.mValue = entityBuffer.readVariant();
                        newProperty.mSync = entityBuffer.readBool();
                        properties[key] = newProperty;
                    }
                    entity->setProperties(properties);
                    
                    // Read components
                    while (!entityBuffer.isEof())
                    {
                        unsigned componentDataSize = entityBuffer.readVLE();
                        VectorBuffer componentBuffer(entityBuffer, componentDataSize);
                        ShortStringHash type = componentBuffer.readShortStringHash();
                        std::string name = componentBuffer.readString();
                        // Only reset an existing component, do not create new at this point
                        Component* component = entity->getComponent(type, name);
                        if (component)
                        {
                            component->load(componentBuffer, mCache);
                            // We should be able to do postload immediately after,
                            // as all depended upon components should exist already
                            component->postLoad(mCache);
                        }
                    }
                }
            }
        }
    }
    catch (...)
    {
    }
}

void Scene::loadAsync(File* file)
{
    if (!mCache)
        return;
    
    if (!file)
    {
        LOGERROR("Null file for async scene loading");
        return;
    }
    
    stopAsyncLoading();
    removeAllEntities();
    
    // Read scene name
    file->seek(0);
    mName = file->readString();
    
    // Read extension properties
    loadProperties(*file);
    
    // Begin async loading
    mAsyncTotalEntities = file->readUInt();
    mAsyncLoadedEntities = 0;
    mAsyncFile = file;
    mAsyncLoading = true;
}

void Scene::loadAsyncXML(File* file)
{
    if (!mCache)
        return;
    
    if (!file)
    {
        LOGERROR("Null file for async XML scene loading");
        return;
    }
    
    file->seek(0);
    SharedPtr<XMLFile> xml(new XMLFile());
    xml->load(*file, mCache);
    XMLElement sceneElem = xml->getRootElement();
    
    stopAsyncLoading();
    removeAllEntities();
    
    // Read scene name
    mName = sceneElem.getString("name");
    
    // Read extension properties
    loadPropertiesXML(sceneElem);
    
    // Count entities
    mAsyncTotalEntities = 0;
    mAsyncLoadedEntities = 0;
    mAsyncXMLElement = sceneElem.getChildElement("entity");
    while (mAsyncXMLElement)
    {
        ++mAsyncTotalEntities;
        mAsyncXMLElement = mAsyncXMLElement.getNextElement("entity");
    }
    
    // Begin async loading
    mAsyncFile = file;
    mAsyncXMLFile = xml;
    mAsyncXMLElement = sceneElem.getChildElement("entity");
    mAsyncLoading = true;
}

void Scene::stopAsyncLoading()
{
    mAsyncLoading = false;
    mAsyncFile.reset();
    mAsyncXMLFile.reset();
    mAsyncXMLElement = XMLElement();
}

void Scene::setName(const std::string& name)
{
    mName = name;
    mNameHash = StringHash(name);
}

void Scene::setNetFlags(unsigned char flags)
{
    // Only the authority or proxy flags can be defined for a scene
    mNetFlags = flags & NET_MODEFLAGS;
}

void Scene::addExtension(SceneExtension* extension)
{
    if (!extension)
        return;
    
    mExtensions[extension->getType()] = extension;
}

void Scene::addComponentFactory(ComponentFactory* factory)
{
    if (!factory)
        return;
    
    mFactories.push_back(SharedPtr<ComponentFactory>(factory));
}

SharedPtr<Component> Scene::createComponent(ShortStringHash type, const std::string& name)
{
    SharedPtr<Component> component;
    
    for (unsigned i = 0; i < mFactories.size(); ++i)
    {
        component = mFactories[i]->createComponent(type, name);
        if (component)
        {
            // Set the authority flag to differentiate between singleplayer & server components
            if (isAuthority())
                component->setNetFlags(component->getNetFlags() | NET_AUTHORITY);
            return component;
        }
    }
    
    EXCEPTION("Could not create unknown component type " + toString(type));
}

Entity* Scene::createEntity(const std::string& name, bool local)
{
    Entity* newEntity = 0;
    
    // If proxy flag is set for the scene, only create local entities
    if (isProxy())
        local = true;
    
    EntityID id;
    if (!local)
        id = getNextEntityID();
    else
        id = getNextLocalEntityID();
    
    newEntity = new Entity(id, name);
    newEntity->mScene = this;
    // Set the authority flag to differentiate between singleplayer & server entities
    if (isAuthority())
        newEntity->setNetFlags(newEntity->getNetFlags() | NET_AUTHORITY);
    
    mEntities[id] = newEntity;
    return newEntity;
}

Entity* Scene::createEntity(EntityID id, const std::string& name)
{
    Entity* newEntity = getEntity(id);
    if (newEntity)
    {
        LOGWARNING("Scene already has entity ID " + toString(id));
        if (!name.empty())
            newEntity->setName(name);
        return newEntity;
    }
    
    newEntity = new Entity(id, name);
    newEntity->mScene = this;
    // Set the authority flag to differentiate between singleplayer & server entities
    if (isAuthority())
        newEntity->setNetFlags(newEntity->getNetFlags() | NET_AUTHORITY);
    
    mEntities[id] = newEntity;
    return newEntity;
}

void Scene::addEntity(Entity* entity)
{
    if (!entity)
    {
        LOGERROR("Null entity for addEntity");
        return;
    }
    
    Scene* oldScene = entity->getScene();
    if (oldScene)
    {
        if (oldScene == this)
        {
            LOGWARNING("Entity " + toString(entity->getID()) + " already in scene");
            return;
        }
        oldScene->removeEntity(entity);
    }
    
    if (hasEntity(entity->getID()))
    {
        LOGWARNING("Scene already has entity ID " + toString(entity->getID()));
        return;
    }
    
    entity->mScene = this;
    // Set the authority flag to differentiate between singleplayer & server entities
    if (isAuthority())
        entity->setNetFlags(entity->getNetFlags() | NET_AUTHORITY);
    
    mEntities[entity->getID()] = entity;
}

void Scene::removeEntity(Entity* entity)
{
    if (!entity)
        return;
    
    for (std::map<EntityID, SharedPtr<Entity> >::iterator i = mEntities.begin(); i != mEntities.end(); ++i)
    {
        if (i->second == entity)
        {
            removeEntity(i);
            return;
        }
    }
    
    LOGWARNING("Entity " + toString(entity->getID()) + " not found in scene");
}

void Scene::removeEntity(EntityID id)
{
    std::map<EntityID, SharedPtr<Entity> >::iterator i = mEntities.find(id);
    if (i != mEntities.end())
    {
        removeEntity(i);
        return;
    }
    
    LOGWARNING("Entity " + toString(id) + " not found in scene");
}

void Scene::removeEntity(const std::string& name)
{
    for (std::map<EntityID, SharedPtr<Entity> >::iterator i = mEntities.begin(); i != mEntities.end(); ++i)
    {
        if (i->second->getName() == name)
        {
            removeEntity(i);
            return;
        }
    }
    
    LOGWARNING("Entity " + name + " not found in scene");
}

void Scene::removeEntity(StringHash nameHash)
{
    for (std::map<EntityID, SharedPtr<Entity> >::iterator i = mEntities.begin(); i != mEntities.end(); ++i)
    {
        if (i->second->getNameHash() == nameHash)
        {
            removeEntity(i);
            return;
        }
    }
    
    LOGWARNING("Entity " + toString(nameHash) + " not found in scene");
}

void Scene::removeAllEntities(unsigned char netFlagsMask)
{
    // Remove all entities with matching netflags
    for (std::map<EntityID, SharedPtr<Entity> >::iterator i = mEntities.begin(); i != mEntities.end();)
    {
        std::map<EntityID, SharedPtr<Entity> >::iterator entity = i;
        ++i;
        if (!netFlagsMask)
            removeEntity(entity);
        else
        {
            if (entity->second->getNetFlags() & netFlagsMask)
                removeEntity(entity);
        }
    }
}

void Scene::resetOwner(Connection* owner, bool removeEntities)
{
    for (std::map<EntityID, SharedPtr<Entity> >::iterator i = mEntities.begin(); i != mEntities.end();)
    {
        // Local entities should not be owned, so stop when local entity ID range reached
        if (i->first >= LOCAL_ENTITY)
            break;
        
        std::map<EntityID, SharedPtr<Entity> >::iterator entity = i;
        ++i;
        
        if (entity->second->getOwner() == owner)
        {
            entity->second->setOwner(0);
            if (removeEntities)
                mEntities.erase(entity);
        }
    }
}

void Scene::setTransientPredictionTime(float time)
{
    mTransientPredictionTime = max(time, 0.0f);
}

void Scene::setInterpolationConstant(float constant)
{
    mInterpolationConstant = constant;
}

void Scene::setInterpolationSnapThreshold(float threshold)
{
    mInterpolationSnapThreshold = threshold * threshold;
}

bool Scene::sendRemoteEvent(StringHash eventType, const VariantMap& eventData, Connection* receiver, float delay, unsigned short timeToLive)
{
    if (!checkRemoteEvent(eventType))
    {
        LOGWARNING("Remote event " + toString(eventType) + " not allowed");
        return false;
    }
    
    // Put to outgoing queue. Server or Client will later assign framenumber and actually send
    mRemoteEvents.push_back(RemoteEvent(eventType, eventData, receiver, delay, timeToLive));
    return true;
}

bool Scene::sendRemoteEvent(Entity* entity, StringHash eventType, const VariantMap& eventData, Connection* receiver, float delay, unsigned short timeToLive)
{
    if (!entity)
    {
        LOGERROR("Null entity for remote event");
        return false;
    }
    if (entity->isLocal())
    {
        LOGWARNING("Can not send remote event to local entity");
        return false;
    }
    if (!checkRemoteEvent(eventType))
    {
        LOGWARNING("Remote event " + toString(eventType) + " not allowed");
        return false;
    }
    
    // Put to outgoing queue. Server or Client will later assign framenumber and actually send
    mRemoteEvents.push_back(RemoteEvent(entity->getID(), eventType, eventData, receiver, delay, timeToLive));
    return true;
}

void Scene::clearQueuedRemoteEvents()
{
    mRemoteEvents.clear();
}

void Scene::addRequiredPackageFile(PackageFile* package)
{
    mRequiredPackages.push_back(SharedPtr<PackageFile>(package));
}


EntityID Scene::getNextEntityID()
{
    unsigned retries = LOCAL_ENTITY - 1;
    for (;;)
    {
        if (!hasEntity(mNextEntityID))
            break;
        mNextEntityID = (mNextEntityID + 1) & (LOCAL_ENTITY - 1);
        if (!mNextEntityID)
            ++mNextEntityID;
        --retries;
        if (!retries)
            EXCEPTION("Non-local entity ID range exhausted");
    }
    
    EntityID current = mNextEntityID;
    
    mNextEntityID = (mNextEntityID + 1) & (LOCAL_ENTITY - 1);
    if (!mNextEntityID)
        ++mNextEntityID;
    
    return current;
}

EntityID Scene::getNextLocalEntityID()
{
    // We should run out of memory before exhausting the local entity ID range, so can loop endlessly
    for (;;)
    {
        if (!hasEntity(mNextLocalEntityID))
            break;
        mNextLocalEntityID = (mNextLocalEntityID + 1);
        if (!mNextLocalEntityID)
            mNextLocalEntityID = LOCAL_ENTITY;
    }
    
    EntityID current = mNextLocalEntityID;
    
    mNextLocalEntityID = (mNextLocalEntityID + 1);
    if (!mNextLocalEntityID)
        mNextLocalEntityID = LOCAL_ENTITY;
    
    return current;
}

bool Scene::hasEntity(EntityID id) const
{
    return mEntities.find(id) != mEntities.end();
}

bool Scene::hasEntity(Entity* entity) const
{
    for (std::map<EntityID, SharedPtr<Entity> >::const_iterator i = mEntities.begin(); i != mEntities.end(); ++i)
    {
        if (i->second == entity)
            return true;
    }
    
    return false;
}

bool Scene::hasEntity(const std::string& name) const
{
    for (std::map<EntityID, SharedPtr<Entity> >::const_iterator i = mEntities.begin(); i != mEntities.end(); ++i)
    {
        if (i->second->getName() == name)
            return true;
    }
    
    return false;
}

bool Scene::hasEntity(StringHash nameHash) const
{
    for (std::map<EntityID, SharedPtr<Entity> >::const_iterator i = mEntities.begin(); i != mEntities.end(); ++i)
    {
        if (i->second->getNameHash() == nameHash)
            return true;
    }
    
    return false;
}

Entity* Scene::getEntity(EntityID id) const
{
    std::map<EntityID, SharedPtr<Entity> >::const_iterator i = mEntities.find(id);
    if (i != mEntities.end())
        return i->second;
    else
        return 0;
}

Entity* Scene::getEntity(const std::string& name) const
{
    for (std::map<EntityID, SharedPtr<Entity> >::const_iterator i = mEntities.begin(); i != mEntities.end(); ++i)
    {
        if (i->second->getName() == name)
            return i->second;
    }
    
    return 0;
}

Entity* Scene::getEntity(StringHash nameHash) const
{
    for (std::map<EntityID, SharedPtr<Entity> >::const_iterator i = mEntities.begin(); i != mEntities.end(); ++i)
    {
        if (i->second->getNameHash() == nameHash)
            return i->second;
    }
    
    return 0;
}

Component* Scene::getComponent(const ComponentRef& ref) const
{
    if (!ref.mEntityID)
        return 0;
    
    Entity* entity = getEntity(ref.mEntityID);
    if (!entity)
    {
        LOGWARNING("Could not resolve component reference (entity ID " + toString(ref.mEntityID) + " hash " +
            toString(ref.mHash) + ")");
        return 0;
    }
    
    // Check if component can be found directly
    const std::vector<SharedPtr<Component> >& components = entity->getComponents();
    for (std::vector<SharedPtr<Component> >::const_iterator i = components.begin(); i != components.end(); ++i)
    {
        if ((*i)->getCombinedHash() == ref.mHash)
            return *i;
    }
    
    // The component may be for example a bone in a model's skeleton. Check children of all scene node components (slow!)
    for (std::vector<SharedPtr<Component> >::const_iterator i = components.begin(); i != components.end(); ++i)
    {
        Node* node = dynamic_cast<Node*>(i->getPtr());
        if (node)
        {
            std::vector<Node*> nodes = node->getChildren(NODE_ANY, true);
            for (std::vector<Node*>::iterator j = nodes.begin(); j != nodes.end(); ++j)
            {
                if ((*j)->getCombinedHash() == ref.mHash)
                    return *j;
            }
        }
    }
    
    LOGWARNING("Could not resolve component reference (entity ID " + toString(ref.mEntityID) + " hash " +
        toString(ref.mHash) + ")");
    return 0;
}

Vector3 Scene::getEntityPosition(Entity* entity) const
{
    static const ShortStringHash rigidBodyHash("RigidBody");
    
    // Get a RigidBody if possible
    // (we can not depend on the actual physics library, so use it like an ordinary scene node)
    Node* body = static_cast<Node*>(entity->getComponent(rigidBodyHash));
    if (body)
        return body->getPosition();
    // Else get any scene node
    Node* node = entity->getDerivedComponent<Node>();
    if (node)
        return node->getPosition();
    // Entity seems to not be positional
    return Vector3::sZero;
}

float Scene::getAsyncLoadProgress() const
{
    if ((!mAsyncLoading) || (!mAsyncTotalEntities))
        return 1.0f;
    else
        return ((float)mAsyncLoadedEntities) / mAsyncTotalEntities;
}

void Scene::setPlayback(bool enable)
{
    mPlayback = enable;
    
    for (std::map<ShortStringHash, SharedPtr<SceneExtension> >::iterator i = mExtensions.begin(); i != mExtensions.end(); ++i)
        i->second->setPlayback(enable);
}

void Scene::removeEntity(std::map<EntityID, SharedPtr<Entity> >::iterator i)
{
    i->second->mScene = 0;
    mEntities.erase(i);
}

void Scene::processRemoteEvents(float timeStep)
{
    for (std::vector<RemoteEvent>::iterator i = mRemoteEvents.begin(); i != mRemoteEvents.end(); ++i)
    {
        if (i->mDelay > 0.0f)
            i->mDelay -= timeStep;
    }
}

void Scene::updateAsyncLoading()
{
    PROFILE(Scene_UpdateAsyncLoading);
    
    // If we somehow got here without a valid file, cancel
    if (!mAsyncFile)
    {
        LOGERROR("Async loading without a valid file");
        stopAsyncLoading();
        return;
    }
    
    Timer asyncTimer;
    
    for (;;)
    {
        if (mAsyncLoadedEntities >= mAsyncTotalEntities)
        {
            finishLoading(*mAsyncFile);
            stopAsyncLoading();
            
            using namespace AsyncLoadFinished;
            
            VariantMap eventData;
            eventData[P_SCENE] = (void*)this;
            sendEvent(EVENT_ASYNCLOADFINISHED, eventData);
            return;
        }
        
        if (!mAsyncXMLFile)
            loadEntity(*mAsyncFile);
        else
            loadEntityXML(mAsyncXMLElement);
        ++mAsyncLoadedEntities;
        
        if (asyncTimer.getMSec(false) >= (1000 / ASYNC_MIN_FPS))
            break;
    }
    
    using namespace AsyncLoadProgress;
    
    VariantMap eventData;
    eventData[P_SCENE] = (void*)this;
    eventData[P_PROGRESS] = getAsyncLoadProgress();
    eventData[P_LOADEDENTITIES] = mAsyncLoadedEntities;
    eventData[P_TOTALENTITIES] = mAsyncTotalEntities;
    sendEvent(EVENT_ASYNCLOADPROGRESS, eventData);
}

void Scene::loadEntity(Deserializer& source)
{
    unsigned entityDataSize = source.readVLE();
    if (entityDataSize)
    {
        // Create the entity and let it load itself
        // Note: a separate buffer is created, then filled in its entirety, so that the stream does not desync
        // if any of the components of this entity fail to load
        VectorBuffer entityData(source, entityDataSize);
        
        EntityID id = entityData.readUInt();
        std::string name = entityData.readString();
        Entity* newEntity = createEntity(id, name);
        
        try
        {
            newEntity->load(entityData, mCache);
            updateNextEntityID(id);
        }
        catch (...)
        {
            LOGERROR("Failed to load entity " + toString(newEntity->getID()));
            removeEntity(newEntity);
        }
    }
}

void Scene::loadEntityXML(XMLElement& source)
{
    // Create the entity and let it load itself
    EntityID id = source.getInt("id");
    std::string name = source.getString("name");
    Entity* newEntity = createEntity(id, name);
    
    try
    {
        newEntity->loadXML(source, mCache);
        updateNextEntityID(id);
    }
    catch (...)
    {
        LOGERROR("Failed to load entity " + toString(newEntity->getID()));
        removeEntity(newEntity);
    }
    
    source = source.getNextElement("entity");
}

void Scene::updateNextEntityID(EntityID loadedID)
{
    if ((loadedID < LOCAL_ENTITY) && (loadedID >= mNextEntityID))
    {
        mNextEntityID = loadedID + 1;
        if (mNextEntityID >= LOCAL_ENTITY)
            mNextEntityID = 1;
    }
    if ((loadedID >= LOCAL_ENTITY) && (loadedID >= mNextLocalEntityID))
    {
        mNextLocalEntityID = loadedID + 1;
        if (!mNextLocalEntityID)
            mNextLocalEntityID = LOCAL_ENTITY;
    }
}

void Scene::finishLoading(Deserializer& source)
{
    // Perform post-load on all entities (resolve entity & component references)
    for (std::map<EntityID, SharedPtr<Entity> >::iterator i = mEntities.begin(); i != mEntities.end(); ++i)
    {
        try
        {
            i->second->postLoad(mCache);
        }
        catch (...)
        {
            LOGERROR("Failed to post-load entity " + toString(i->second->getID()));
        }
    }
    
    // Store the name of scene source (needed in networking to load the correct scene on the client)
    mFileName = source.getName();
    
    // If we loaded from a file, store the file checksum as scene checksum
    File* file = dynamic_cast<File*>(&source);
    if (file)
        mChecksum = file->getChecksum();
    else
        mChecksum = 0;
}
