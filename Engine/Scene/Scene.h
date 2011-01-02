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

#ifndef SCENE_SCENE_H
#define SCENE_SCENE_H

#include "BoundingBox.h"
#include "DelayedEventQueue.h"
#include "Entity.h"
#include "RemoteEvent.h"
#include "VectorBuffer.h"
#include "XMLElement.h"

class ComponentFactory;
class Deserializer;
class Engine;
class File;
class Octree;
class PackageFile;
class PhysicsWorld;
class ResourceCache;
class SceneExtension;
class Serializer;
class XMLFile;

//! A simulated world consisting of entities
class Scene : public RefCounted, public EventListener, public DelayedEventQueue
{
public:
    //! Construct with resource cache pointer and name
    Scene(ResourceCache* cache, const std::string& name = "Default");
    //! Destruct
    virtual ~Scene();
    
    //! Run update. Send update events and update scene extensions
    void update(float timeStep);
    //! Perform client-side visual smoothing
    void interpolate(float timeStep);
    //! Write to a stream
    void save(Serializer& dest, bool throwOnError = true);
    //! Read from a stream
    void load(Deserializer& source, bool throwOnError = true);
    //! Write to an XML file
    void saveXML(const std::string& fileName, bool throwOnError = true);
    //! Read from an XML file
    void loadXML(Deserializer& source, bool throwOnError = true);
    //! Write properties only to a stream
    void saveProperties(Serializer& dest);
    //! Read properties only from a stream
    void loadProperties(Deserializer& source);
    //! Write properties only to an XML element
    void savePropertiesXML(XMLElement& dest);
    //! Read properties only from an XML element
    void loadPropertiesXML(const XMLElement& source);
    //! Store predicted entities so that their state can be rewound
    void storePredictedEntities();
    //! Restore predicted entities to stored state
    void restorePredictedEntities();
    //! Begin asynchronous loading
    void loadAsync(File* file);
    //! Begin asynchronous loading from an XML file
    void loadAsyncXML(File* file);
    //! Stop asynchronous loading
    void stopAsyncLoading();
    
    //! Set scene name
    void setName(const std::string& name);
    //! Set network replication flags (only NET_AUTHORITY or NET_PROXY)
    void setNetFlags(unsigned char flags);
    //! Add a scene extension
    void addExtension(SceneExtension* extension);
    //! Add a component factory
    void addComponentFactory(ComponentFactory* factory);
    //! Create a component. Throw exception if no factory can create
    SharedPtr<Component> createComponent(ShortStringHash type, const std::string& name = std::string());
    //! Create an entity and assign an ID automatically
    Entity* createEntity(const std::string& name = std::string(), bool local = false);
    //! Create an entity with manually defined ID
    Entity* createEntity(EntityID id, const std::string& name = std::string());
    //! Add an existing entity
    void addEntity(Entity* entity);
    //! Remove an entity by ID. This is preferred for performance
    void removeEntity(EntityID id);
    //! Remove an entity by pointer. Needs to search through all entities
    void removeEntity(Entity* entity);
    //! Remove an entity by name. Needs to search through all entities
    void removeEntity(const std::string& name);
    //! Remove an entity by name hash. Needs to search through all entities
    void removeEntity(StringHash nameHash);
    //! Remove all entities
    void removeAllEntities(unsigned char netFlagsMask = NET_NONE);
    //! Reset a specific network owner from entities. Optionally remove the owned entities
    void resetOwner(Connection* owner, bool removeEntities = false);
    //! Set client-side transient prediction time
    void setTransientPredictionTime(float time);
    //! Set visual smoothing constant
    void setInterpolationConstant(float constant);
    //! Set visual smoothing position snap threshold
    void setInterpolationSnapThreshold(float threshold);
    //! Queue a remote event to be sent
    bool sendRemoteEvent(StringHash eventType, const VariantMap& eventData = VariantMap(), Connection* receiver = 0, float delay = 0.0f, unsigned short timeToLive = 0);
    //! Queue a remote entity event to be sent
    bool sendRemoteEvent(Entity* entity, StringHash eventType, const VariantMap& eventData = VariantMap(), Connection* receiver = 0, float delay = 0.0f, unsigned short timeToLive = 0);
    //! Clear all queued remote events
    void clearQueuedRemoteEvents();
    //! Mark a package file as required (server only)
    void addRequiredPackageFile(PackageFile* package);
    //! Return next non-local entity ID. Throw exception if no more free ID's
    EntityID getNextEntityID();
    //! Return next local entity ID
    EntityID getNextLocalEntityID();
    //! Template version of creating a component. Throw exception if no factory can create
    template <class T> SharedPtr<T> createComponent(const std::string& name = std::string());
    
    //! Return scene name
    const std::string& getName() const { return mName; }
    //! Return scene name hash
    StringHash getNameHash() const { return mNameHash; }
    //! Return network replication flags
    unsigned char getNetFlags() const { return mNetFlags; }
    //! Return resource cache
    ResourceCache* getResourceCache() const { return mCache; }
    //! Return scene extensions
    const std::map<ShortStringHash, SharedPtr<SceneExtension> >& getExtensions() const { return mExtensions; }
    //! Return component factories
    const std::vector<SharedPtr<ComponentFactory> >& getComponentFactories() const { return mFactories; }
    //! Return whether has an entity by ID. This is preferred for performance
    bool hasEntity(EntityID id) const;
    //! Return whether has an entity by pointer. Needs to search through all entities
    bool hasEntity(Entity* entity) const;
    //! Return whether has an entity by name. Needs to search through all entities
    bool hasEntity(const std::string& name) const;
    //! Return whether has an entity by name hash. Needs to search through all entities
    bool hasEntity(StringHash nameHash) const;
    //! Return entity by ID, or null if not found. This is preferred for performance
    Entity* getEntity(EntityID id) const;
    //! Return entity by name, or null if not found. Needs to search through all entities
    Entity* getEntity(const std::string& name) const;
    //! Return entity by name hash, or null if not found. Needs to search through all entities
    Entity* getEntity(StringHash nameHash) const;
    //! Return all entities
    const std::map<EntityID, SharedPtr<Entity> >& getEntities() const { return mEntities; }
    //! Return a component by component reference, or null if not found
    Component* getComponent(const ComponentRef& ref) const;
    //! Return entity position by going through scene node components it has (RigidBody is preferred)
    Vector3 getEntityPosition(Entity* entity) const;
    //! Return queued remote events
    std::vector<RemoteEvent>& getQueuedRemoteEvents() { return mRemoteEvents; }
    //! Return required package files
    const std::vector<SharedPtr<PackageFile> >& getRequiredPackageFiles() const { return mRequiredPackages; }
    //! Return scene file name
    const std::string& getFileName() const { return mFileName; }
    //! Return scene file checksum
    unsigned getChecksum() const { return mChecksum; }
    //! Return client-side transient prediction time
    float getTransientPredictionTime() const { return mTransientPredictionTime; }
    //! Return visual smoothing interpolation constant
    float getInterpolationConstant() { return mInterpolationConstant; }
    //! Return visual smoothing lerp factor, valid only during update()
    float getInterpolationLerpFactor() { return mInterpolationLerpFactor; }
    //! Return visual smoothing position snap threshold
    float getInterpolationSnapThreshold() { return sqrtf(mInterpolationSnapThreshold); }
    //! Return visual smoothing squared position snap threshold
    float getInterpolationSnapThresholdSquared() { return mInterpolationSnapThreshold; }
    //! Return asynchronous loading progress between 0.0 - 1.0
    float getAsyncLoadProgress() const;
    //! Return whether scene is performing client-side prediction by replaying controls
    bool isPlayback() const { return mPlayback; }
    //! Return whether is a server scene
    bool isAuthority() const { return (mNetFlags & NET_AUTHORITY) != 0; }
    //! Return whether is a client scene
    bool isProxy() const { return (mNetFlags & NET_PROXY) != 0; }
    //! Return whether is loading asynchronously
    bool isAsyncLoading() const { return mAsyncLoading; }
    //! Template function that returns a specific scene extension
    template <class T> T* getExtension() const;
    
    //! Set client-side prediction controls playback mode. Called by Client
    void setPlayback(bool enable);
    
private:
    //! Remove an entity by iterator
    void removeEntity(std::map<EntityID, SharedPtr<Entity> >::iterator i);
    //! Update remote events' delay timers
    void processRemoteEvents(float timeStep);
    //! Update asynchronous loading. Load entities until a set time has passed
    void updateAsyncLoading();
    //! Load an entity from a stream
    void loadEntity(Deserializer& source, bool throwOnError);
    //! Load an entity from an XML element
    void loadEntityXML(XMLElement& source, bool throwOnError);
    //! Update next entity ID's after loading an entity
    void updateNextEntityID(EntityID loadedID);
    //! Perform post-load after scene loading has finished
    void finishLoading(Deserializer& source, bool throwOnError);
    
    //! Scene name
    std::string mName;
    //! Scene name hash
    StringHash mNameHash;
    //! Resource cache
    SharedPtr<ResourceCache> mCache;
    //! Scene extensions
    std::map<ShortStringHash, SharedPtr<SceneExtension> > mExtensions;
    //! Component factories
    std::vector<SharedPtr<ComponentFactory> > mFactories;
    //! Entities
    std::map<EntityID, SharedPtr<Entity> > mEntities;
    //! Queued remote events
    std::vector<RemoteEvent> mRemoteEvents;
    //! Required package files
    std::vector<SharedPtr<PackageFile> > mRequiredPackages;
    //! Scene file name
    std::string mFileName;
    //! Next non-local entity ID
    EntityID mNextEntityID;
    //! Next local entity ID
    EntityID mNextLocalEntityID;
    //! Buffer for predicted entity data
    VectorBuffer mPredictedEntityData;
    //! Network replication flags
    unsigned char mNetFlags;
    //! Scene file checksum
    unsigned mChecksum;
    //! Client-side transient prediction time
    float mTransientPredictionTime;
    //! Visual smoothing interpolation constant
    float mInterpolationConstant;
    //! Visual smoothing squared snap threshodl
    float mInterpolationSnapThreshold;
    //! Visual smoothing lerp factor, valid only during update()
    float mInterpolationLerpFactor;
    //! Client-side prediction controls playback flag
    bool mPlayback;
    
    //! File used in asynchronous loading
    SharedPtr<File> mAsyncFile;
    //! XML file used in asynchronous loading
    SharedPtr<XMLFile> mAsyncXMLFile;
    //! Current XML element in asynchronous loading
    XMLElement mAsyncXMLElement;
    //! Total entities to be loaded asynchronously
    unsigned mAsyncTotalEntities;
    //! Entities loaded so far
    unsigned mAsyncLoadedEntities;
    //! Asynchronous loading flag
    bool mAsyncLoading;
};

template <class T> SharedPtr<T> Scene::createComponent(const std::string& name)
{
    return staticCast<T>(createComponent(T::getTypeStatic(), name));
}

template <class T> T* Scene::getExtension() const
{
    ShortStringHash type = T::getTypeStatic();
    std::map<ShortStringHash, SharedPtr<SceneExtension> >::const_iterator i = mExtensions.find(type);
    if (i == mExtensions.end())
        return 0;
    return static_cast<T*>(i->second.getPtr());
}

#endif // SCENE_SCENE_H
