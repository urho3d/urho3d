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
#include "RegisterTemplates.h"
#include "Scene.h"
#include "ScriptInstance.h"

static void ConstructComponentRef(ComponentRef* ptr)
{
    new(ptr) ComponentRef();
}

static void ConstructComponentRefCopy(const ComponentRef& ref, ComponentRef* ptr)
{
    new(ptr) ComponentRef(ref);
}

static void ConstructComponentRefInit(Component* component, bool forXML, ComponentRef* ptr)
{
    new(ptr) ComponentRef(component, forXML);
}

static void DestructComponentRef(ComponentRef* ptr)
{
    ptr->~ComponentRef();
}

static void SendComponentEvent(Component* component, const std::string& eventType, VariantMap& eventData)
{
    EventListener* listener = dynamic_cast<EventListener*>(component);
    if (listener)
        sendEvent(listener, StringHash(eventType), eventData);
}

static void registerComponent(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("const uint8 NET_NONE", (void*)&NET_NONE);
    engine->RegisterGlobalProperty("const uint8 NET_AUTHORITY", (void*)&NET_AUTHORITY);
    engine->RegisterGlobalProperty("const uint8 NET_PROXY", (void*)&NET_PROXY);
    engine->RegisterGlobalProperty("const uint8 NET_OWNER", (void*)&NET_OWNER);
    engine->RegisterGlobalProperty("const uint8 NET_OWNERPREDICT", (void*)&NET_OWNERPREDICT);
    engine->RegisterGlobalProperty("const uint8 NET_TRANSIENTPREDICT", (void*)&NET_TRANSIENTPREDICT);
    engine->RegisterGlobalProperty("const uint8 NET_SYNCTOALL", (void*)&NET_SYNCTOALL);
    engine->RegisterGlobalProperty("const uint8 NET_SYNCTOOWNER", (void*)&NET_SYNCTOOWNER);
    engine->RegisterGlobalProperty("const uint8 NET_SYNCTONONE", (void*)&NET_SYNCTONONE);
    engine->RegisterGlobalProperty("const uint8 NET_MODEFLAGS", (void*)&NET_MODEFLAGS);
    engine->RegisterGlobalProperty("const uint8 NET_PREDICTIONFLAGS", (void*)&NET_PREDICTIONFLAGS);
    engine->RegisterGlobalProperty("const uint8 NET_SYNCFLAGS", (void*)&NET_SYNCFLAGS);
    
    engine->RegisterObjectType("Entity", 0, asOBJ_REF);
    registerComponent<Component>(engine, "Component");
    
    engine->RegisterGlobalFunction("void sendEvent(Component@+, const string& in, VariantMap&)", asFUNCTION(SendComponentEvent), asCALL_CDECL);
}

static void registerComponentRef(asIScriptEngine* engine)
{
    engine->RegisterObjectType("ComponentRef", sizeof(ComponentRef), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
    engine->RegisterObjectBehaviour("ComponentRef", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructComponentRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("ComponentRef", asBEHAVE_CONSTRUCT, "void f(const ComponentRef& in)", asFUNCTION(ConstructComponentRefCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("ComponentRef", asBEHAVE_CONSTRUCT, "void f(Component@+, bool)", asFUNCTION(ConstructComponentRefInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("ComponentRef", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructComponentRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ComponentRef", "ComponentRef &opAssign(const ComponentRef& in)", asMETHOD(ComponentRef, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("ComponentRef", "void write(Serializer&)", asMETHOD(ComponentRef, write), asCALL_THISCALL);
    engine->RegisterObjectMethod("ComponentRef", "void read(Deserializer&)", asMETHOD(ComponentRef, read), asCALL_THISCALL);
    engine->RegisterObjectMethod("ComponentRef", "void writeXML(XMLElement&)", asMETHOD(ComponentRef, writeXML), asCALL_THISCALL);
    engine->RegisterObjectMethod("ComponentRef", "void readXML(const XMLElement&)", asMETHOD(ComponentRef, readXML), asCALL_THISCALL);
    engine->RegisterObjectProperty("ComponentRef", "uint entityID", offsetof(ComponentRef, mEntityID));
    engine->RegisterObjectProperty("ComponentRef", "ShortStringHash hash", offsetof(ComponentRef, mHash));
    engine->RegisterObjectProperty("ComponentRef", "string typeName", offsetof(ComponentRef, mTypeName));
    engine->RegisterObjectProperty("ComponentRef", "string name", offsetof(ComponentRef, mName));
    engine->RegisterObjectProperty("ComponentRef", "bool dirty", offsetof(ComponentRef, mDirty));
}

Component* EntityCreateComponent(const std::string& type, Entity* ptr)
{
    try
    {
        return ptr->createComponent(ShortStringHash(type));
    }
    catch (Exception& e)
    {
        SAFE_RETHROW_RET(e, 0);
    }
}

static Component* EntityCreateComponentWithName(const std::string& type, const std::string& name, Entity* ptr)
{
    try
    {
        return ptr->createComponent(ShortStringHash(type), name);
    }
    catch (Exception& e)
    {
        SAFE_RETHROW_RET(e, 0);
    }
}

static void EntityRemoveComponent(const std::string& type, Entity* ptr)
{
    ptr->removeComponent(ShortStringHash(type));
}

static void EntityRemoveComponentWithName(const std::string& type, const std::string& name, Entity* ptr)
{
    ptr->removeComponent(ShortStringHash(type), name);
}

static void EntitySetProperty(const std::string& name, const Variant& value, Entity* ptr)
{
    ptr->setProperty(ShortStringHash(name), value);
}

static void EntitySetPropertyWithSync(const std::string& name, const Variant& value, bool sync, Entity* ptr)
{
    ptr->setProperty(ShortStringHash(name), value, sync);
}

static void EntitySetPropertySync(const std::string& name, bool sync, Entity* ptr)
{
    ptr->setPropertySync(ShortStringHash(name), sync);
}

static void EntityRemoveProperty(const std::string& name, Entity* ptr)
{
    ptr->removeProperty(ShortStringHash(name));
}

static const Variant& EntityGetProperty(const std::string& name, Entity* ptr)
{
    return ptr->getProperty(ShortStringHash(name));
}

static bool EntityGetPropertySync(const std::string& name, Entity* ptr)
{
    return ptr->getPropertySync(ShortStringHash(name));
}

static bool EntityHasComponent(const std::string& type, Entity* ptr)
{
    return ptr->hasComponent(ShortStringHash(type));
}

static bool EntityHasComponentWithName(const std::string& type, const std::string& name, Entity* ptr)
{
    return ptr->hasComponent(ShortStringHash(type), name);
}

static Component* EntityGetComponent(const std::string& type, Entity* ptr)
{
    return ptr->getComponent(ShortStringHash(type));
}

static Component* EntityGetComponentWithName(const std::string& type, const std::string& name, Entity* ptr)
{
    return ptr->getComponent(ShortStringHash(type), name);
}

static Entity* GetEntity()
{
    return getScriptContextEntity();
}

static void SendEntityEvent(Entity* entity, const std::string& eventType, VariantMap& eventData)
{
    sendEvent(entity, StringHash(eventType), eventData);
}

static void registerEntity(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("const uint LOCAL_ENTITY", (void*)&LOCAL_ENTITY);
    
    engine->RegisterObjectType("Scene", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Entity", asBEHAVE_ADDREF, "void f()", asMETHOD(Entity, addRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("Entity", asBEHAVE_RELEASE, "void f()", asMETHOD(Entity, releaseRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "void setName(const string& in)", asMETHOD(Entity, setName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "void setNetFlags(uint8)", asMETHOD(Entity, setNetFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "void setProperty(const string& in, const Variant& in)", asFUNCTION(EntitySetProperty), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Entity", "void setProperty(const string& in, const Variant& in, bool)", asFUNCTION(EntitySetPropertyWithSync), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Entity", "void setPropertySync(const string& in, bool)", asFUNCTION(EntitySetPropertySync), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Entity", "void removeProperty(const string& in)", asFUNCTION(EntityRemoveProperty), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Entity", "void removeAllProperties()", asMETHOD(Entity, removeAllProperties), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "void setNetUpdateDistance(float)", asMETHOD(Entity, setNetUpdateDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "void setPredictionTimer(float)", asMETHOD(Entity, setPredictionTimer), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "void setPredictionFrom(Entity@+)", asMETHOD(Entity, setPredictionFrom), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "Component@+ createComponent(const string& in)", asFUNCTION(EntityCreateComponent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Entity", "Component@+ createComponent(const string& in, const string& in)", asFUNCTION(EntityCreateComponentWithName), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Entity", "void addComponent(Component@+)", asMETHOD(Entity, addComponent), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "void removeComponent(Component@+)", asMETHODPR(Entity, removeComponent, (Component*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "void removeComponent(const string& in)", asFUNCTION(EntityRemoveComponent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Entity", "void removeComponent(const string& in, const string& in)", asFUNCTION(EntityRemoveComponentWithName), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Entity", "uint getID() const", asMETHOD(Entity, getID), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "bool isLocal() const", asMETHOD(Entity, isLocal), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "const string& getName() const", asMETHOD(Entity, getName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "uint8 getNetFlags() const", asMETHOD(Entity, getNetFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "Scene@+ getScene() const", asMETHOD(Entity, getScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "const Variant& getProperty(const string& in)", asFUNCTION(EntityGetProperty), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Entity", "bool getPropertySync(const string& in)", asFUNCTION(EntityGetPropertySync), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Entity", "float getNetUpdateDistance() const", asMETHOD(Entity, getNetUpdateDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "float getPredictionTimer() const", asMETHOD(Entity, getPredictionTimer), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "string getUniqueComponentName()", asMETHOD(Entity, getUniqueComponentName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "bool hasComponent(const string& in) const", asFUNCTION(EntityHasComponent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Entity", "bool hasComponent(const string& in, const string& in) const", asFUNCTION(EntityHasComponentWithName), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Entity", "Component@+ getComponent(const string& in) const", asFUNCTION(EntityGetComponent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Entity", "Component@+ getComponent(const string& in, const string& in) const", asFUNCTION(EntityGetComponentWithName), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Entity", "bool isAuthority() const", asMETHOD(Entity, isAuthority), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "bool isProxy() const", asMETHOD(Entity, isProxy), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "bool isOwnerPredicted() const", asMETHOD(Entity, isOwnerPredicted), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "bool isTransientPredicted() const", asMETHOD(Entity, isTransientPredicted), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "bool isPlayback() const", asMETHOD(Entity, isPlayback), asCALL_THISCALL);
    
    engine->RegisterGlobalFunction("Entity@+ getEntity()", asFUNCTION(GetEntity), asCALL_CDECL);
    engine->RegisterGlobalFunction("Entity@+ get_entity()", asFUNCTION(GetEntity), asCALL_CDECL);
    engine->RegisterGlobalFunction("void sendEvent(Entity@+, const string& in, VariantMap&)", asFUNCTION(SendEntityEvent), asCALL_CDECL);
    
    // Register Variant getPtr() for Entity
    engine->RegisterObjectMethod("Variant", "Entity@+ getEntity() const", asFUNCTION(getVariantPtr<Entity>), asCALL_CDECL_OBJLAST);
}

static Scene* GetScene()
{
    return getScriptContextScene();
}

static Entity* SceneCreateEntity(Scene* ptr)
{
    try
    {
        return ptr->createEntity();
    }
    catch (Exception& e)
    {
        SAFE_RETHROW_RET(e, 0);
    }
}

static Entity* SceneCreateEntityWithName(const std::string& name, Scene* ptr)
{
    try
    {
        return ptr->createEntity(name);
    }
    catch (Exception& e)
    {
        SAFE_RETHROW_RET(e, 0);
    }
}

static Entity* SceneCreateEntityWithNameAndLocalFlag(const std::string& name, bool local, Scene* ptr)
{
    try
    {
        return ptr->createEntity(name, local);
    }
    catch (Exception& e)
    {
        SAFE_RETHROW_RET(e, 0);
    }
}

static void SceneSave(File* file, Scene* ptr)
{
    if (!file)
        SAFE_EXCEPTION("Null scene destination file");
    try
    {
        ptr->save(*file);
    }
    catch (Exception& e)
    {
        SAFE_RETHROW(e);
    }
}

static void SceneLoad(File* file, Scene* ptr)
{
    if (!file)
        SAFE_EXCEPTION("Null scene source file");
    try
    {
        ptr->load(*file);
    }
    catch (Exception& e)
    {
        SAFE_RETHROW(e);
    }
}

static void SceneSaveXML(File* file, Scene* ptr)
{
    if (!file)
        SAFE_EXCEPTION("Null scene destination XML file");
    try
    {
        ptr->saveXML(*file);
    }
    catch (Exception& e)
    {
        SAFE_RETHROW(e);
    }
}

static void SceneLoadXML(File* file, Scene* ptr)
{
    if (!file)
        SAFE_EXCEPTION("Null scene source XML file");
    try
    {
        ptr->loadXML(*file);
    }
    catch (Exception& e)
    {
        SAFE_RETHROW(e);
    }
}

static void SceneLoadAsync(File* file, Scene* ptr)
{
    try
    {
        ptr->loadAsync(file);
    }
    catch (Exception& e)
    {
        SAFE_RETHROW(e);
    }
}

static void SceneLoadAsyncXML(File* file, Scene* ptr)
{
    try
    {
        ptr->loadAsyncXML(file);
    }
    catch (Exception& e)
    {
        SAFE_RETHROW(e);
    }
}

static CScriptArray* SceneGetEntities(Scene* ptr)
{
    const std::map<EntityID, SharedPtr<Entity> >& entities = ptr->getEntities();
    std::vector<Entity*> result;
    for (std::map<EntityID, SharedPtr<Entity> >::const_iterator i = entities.begin(); i != entities.end(); ++i)
        result.push_back(i->second);
    return vectorToHandleArray<Entity*>(result, "array<Entity@>");
}

static CScriptArray* SceneGetEntitiesWithClass(const std::string& className, Scene* ptr)
{
    const std::map<EntityID, SharedPtr<Entity> >& entities = ptr->getEntities();
    std::vector<Entity*> result;
    for (std::map<EntityID, SharedPtr<Entity> >::const_iterator i = entities.begin(); i != entities.end(); ++i)
    {
        const std::vector<SharedPtr<Component> >& components = i->second->getComponents();
        for (std::vector<SharedPtr<Component> >::const_iterator j = components.begin(); j != components.end(); ++j)
        {
            if ((*j)->getType() == ScriptInstance::getTypeStatic())
            {
                ScriptInstance* instance = static_cast<ScriptInstance*>(j->getPtr());
                if (instance->getClassName() == className)
                {
                    result.push_back(i->second);
                    break;
                }
            }
        }
    }
    
    return vectorToHandleArray<Entity*>(result, "array<Entity@>");
}

static void SendDelayedEvent(const std::string& eventType, const VariantMap& eventData, float delay)
{
    Scene* scene = getScriptContextScene();
    if (scene)
        scene->sendDelayedEvent(StringHash(eventType), eventData, delay);
}

static void SendDelayedEntityEvent(Entity* entity, const std::string& eventType, const VariantMap& eventData, float delay)
{
    Scene* scene = getScriptContextScene();
    if (scene)
        scene->sendDelayedEvent(entity, StringHash(eventType), eventData, delay);
}

static void SendDelayedComponentEvent(Component* component, const std::string& eventType, const VariantMap& eventData, float delay)
{
    Scene* scene = getScriptContextScene();
    if (scene)
    {
        EventListener* listener = dynamic_cast<EventListener*>(component);
        if (listener)
            scene->sendDelayedEvent(listener, StringHash(eventType), eventData, delay);
    }
}

static void ClearDelayedEvents()
{
    Scene* scene = getScriptContextScene();
    if (scene)
        scene->clearDelayedEvents();
}

static void registerScene(asIScriptEngine* engine)
{
    engine->RegisterObjectBehaviour("Scene", asBEHAVE_ADDREF, "void f()", asMETHOD(Scene, addRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("Scene", asBEHAVE_RELEASE, "void f()", asMETHOD(Scene, releaseRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void save(File@+)", asFUNCTION(SceneSave), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "void load(File@+)", asFUNCTION(SceneLoad), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "void saveXML(File@+)", asFUNCTION(SceneSaveXML), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "void loadXML(File@+)", asFUNCTION(SceneLoadXML), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "void loadAsync(File@+)", asFUNCTION(SceneLoadAsync), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "void loadAsyncXML(File@+)", asFUNCTION(SceneLoadAsyncXML), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "Entity@+ createEntity()", asFUNCTION(SceneCreateEntity), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "Entity@+ createEntity(const string& in)", asFUNCTION(SceneCreateEntityWithName), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "Entity@+ createEntity(const string& in, bool)", asFUNCTION(SceneCreateEntityWithNameAndLocalFlag), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "void addEntity(Entity@+)", asMETHOD(Scene, addEntity), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void removeEntity(uint)", asMETHODPR(Scene, removeEntity, (EntityID), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void removeEntity(Entity@+)", asMETHODPR(Scene, removeEntity, (Entity*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void removeEntity(const string& in)", asMETHODPR(Scene, removeEntity, (const std::string&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void removeEntity(uint)", asMETHODPR(Scene, removeEntity, (EntityID), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void removeAllEntities(uint8)", asMETHOD(Scene, removeAllEntities), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void setTransientPredictionTime(float)", asMETHOD(Scene, setTransientPredictionTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void setInterpolationConstant(float)", asMETHOD(Scene, setInterpolationConstant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void setInterpolationSnapThreshold(float)", asMETHOD(Scene, setInterpolationSnapThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const string& getName() const", asMETHOD(Scene, getName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool hasEntity(uint) const", asMETHODPR(Scene, hasEntity, (EntityID) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool hasEntity(Entity@+) const", asMETHODPR(Scene, hasEntity, (Entity*) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool hasEntity(const string& in) const", asMETHODPR(Scene, hasEntity, (const std::string&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Entity@+ getEntity(uint) const", asMETHODPR(Scene, getEntity, (EntityID) const, Entity*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Entity@+ getEntity(const string& in) const", asMETHODPR(Scene, getEntity, (const std::string&) const, Entity*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "array<Entity@>@ getEntities() const", asFUNCTION(SceneGetEntities), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "array<Entity@>@ getEntities(const string& in) const", asFUNCTION(SceneGetEntitiesWithClass), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "Vector3 getEntityPosition(Entity@+) const", asMETHOD(Scene, getEntityPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float getTransientPredictionTime() const", asMETHOD(Scene, getTransientPredictionTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float getInterpolationConstant() const" ,asMETHOD(Scene, getInterpolationConstant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float getInterpolationLerpFactor() const" ,asMETHOD(Scene, getInterpolationLerpFactor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float getInterpolationSnapThreshold() const", asMETHOD(Scene, getInterpolationSnapThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float getInterpolationSnapThresholdSquared() const", asMETHOD(Scene, getInterpolationSnapThresholdSquared), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float getAsyncLoadProgress() const", asMETHOD(Scene, getAsyncLoadProgress), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool isAuthority() const", asMETHOD(Scene, isAuthority), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool isProxy() const", asMETHOD(Scene, isProxy), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool isPlayback() const", asMETHOD(Scene, isPlayback), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool isAsyncLoading() const", asMETHOD(Scene, isAsyncLoading), asCALL_THISCALL);
    
    engine->RegisterGlobalFunction("Scene@+ getScene()", asFUNCTION(GetScene), asCALL_CDECL);
    engine->RegisterGlobalFunction("Scene@+ get_scene()", asFUNCTION(GetScene), asCALL_CDECL);
    
    // Add delayed event functionality as global functions because the Scene can be found out through the context
    engine->RegisterGlobalFunction("void sendDelayedEvent(const string& in, const VariantMap& in, float)", asFUNCTION(SendDelayedEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void sendDelayedEvent(Entity@+, const string& in, const VariantMap& in, float)", asFUNCTION(SendDelayedEntityEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void sendDelayedEvent(Component@+, const string& in, const VariantMap& in, float)", asFUNCTION(SendDelayedComponentEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void clearDelayedEvents()", asFUNCTION(ClearDelayedEvents), asCALL_CDECL);
    
    // Register Variant getPtr() for Scene
    engine->RegisterObjectMethod("Variant", "Scene@+ getScene() const", asFUNCTION(getVariantPtr<Scene>), asCALL_CDECL_OBJLAST);
}

static void registerNode(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("const uint NODE_NONE", (void*)&NODE_NONE);
    engine->RegisterGlobalProperty("const uint NODE_NODE", (void*)&NODE_NODE);
    engine->RegisterGlobalProperty("const uint NODE_CAMERA", (void*)&NODE_CAMERA);
    engine->RegisterGlobalProperty("const uint NODE_BONE", (void*)&NODE_BONE);
    engine->RegisterGlobalProperty("const uint NODE_GEOMETRY", (void*)&NODE_GEOMETRY);
    engine->RegisterGlobalProperty("const uint NODE_LIGHT", (void*)&NODE_LIGHT);
    engine->RegisterGlobalProperty("const uint NODE_STATICMODEL", (void*)&NODE_STATICMODEL);
    engine->RegisterGlobalProperty("const uint NODE_ANIMATEDMODEL", (void*)&NODE_ANIMATEDMODEL);
    engine->RegisterGlobalProperty("const uint NODE_INSTANCEDMODEL", (void*)&NODE_INSTANCEDMODEL);
    engine->RegisterGlobalProperty("const uint NODE_BILLBOARDSET", (void*)&NODE_BILLBOARDSET);
    engine->RegisterGlobalProperty("const uint NODE_CUSTOMOBJECT", (void*)&NODE_CUSTOMOBJECT);
    engine->RegisterGlobalProperty("const uint NODE_SKYBOX", (void*)&NODE_SKYBOX);
    engine->RegisterGlobalProperty("const uint NODE_ZONE", (void*)&NODE_ZONE);
    engine->RegisterGlobalProperty("const uint NODE_RIGIDBODY", (void*)&NODE_RIGIDBODY);
    engine->RegisterGlobalProperty("const uint NODE_POSITIONALCHANNEL", (void*)&NODE_POSITIONALCHANNEL);
    engine->RegisterGlobalProperty("const uint NODE_ANY", (void*)&NODE_ANY);
    
    registerNode<Node>(engine, "Node");
    registerRefCasts<Component, Node>(engine, "Component", "Node");
}

void registerSceneLibrary(asIScriptEngine* engine)
{
    registerComponent(engine);
    registerComponentRef(engine);
    registerEntity(engine);
    registerScene(engine);
    registerNode(engine);
}
