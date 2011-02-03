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
#include "PhysicsEvents.h"
#include "PhysicsWorld.h"
#include "RegisterArray.h"
#include "ReplicationUtils.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "ScriptEngine.h"
#include "ScriptFile.h"
#include "ScriptInstance.h"
#include "StringUtils.h"

#include <angelscript.h>

#include "DebugNew.h"

static const std::string methodDeclarations[] = {
    "void start()",
    "void stop()",
    "void update(float)",
    "void postUpdate(float)",
    "void updateFixed(float)",
    "void postUpdateFixed(float)",
    "void save(Serializer&)",
    "void load(Deserializer&)",
    "void postLoad()",
    "void saveXML(XMLElement&)",
    "void loadXML(const XMLElement&)",
    "void writeNetUpdate(Serializer&, const NetUpdateInfo&)",
    "void readNetUpdate(Deserializer&, const NetUpdateInfo&)",
    "void postNetUpdate()",
    "void interpolate(bool)",
    "array<ComponentRef> getComponentRefs()",
    "array<Resource@> getResourceRefs()"
};

std::map<void*, ScriptInstance*> objectToInstance;

ScriptInstance::ScriptInstance(ScriptEngine* scriptEngine, const std::string& name) :
    Component(name),
    mScriptEngine(scriptEngine),
    mScriptObject(0),
    mEnabled(true)
{
    if (!mScriptEngine)
        EXCEPTION("Null script engine for ScriptInstance");
    
    clearMethods();
}

ScriptInstance::~ScriptInstance()
{
    releaseObject();
}

void ScriptInstance::save(Serializer& dest)
{
    Component::save(dest);
    
    dest.writeBool(mEnabled);
    dest.writeStringHash(getResourceHash(mScriptFile));
    dest.writeString(mClassName);
    
    // Save script's data into a separate buffer for safety
    static VectorBuffer scriptBuffer;
    scriptBuffer.clear();
    if (mMethods[METHOD_SAVE])
    {
        std::vector<Variant> parameters;
        parameters.push_back(Variant((void*)static_cast<Serializer*>(&scriptBuffer)));
        mScriptFile->execute(mScriptObject, mMethods[METHOD_SAVE], parameters);
    }
    dest.writeVLE(scriptBuffer.getSize());
    dest.write(scriptBuffer.getData(), scriptBuffer.getSize());
}

void ScriptInstance::load(Deserializer& source, ResourceCache* cache)
{
    Component::load(source, cache);
    
    mEnabled = source.readBool();
    StringHash scriptFile = source.readStringHash();
    std::string className = source.readString();
    setScriptClass(cache->getResource<ScriptFile>(scriptFile), className);
    
    static VectorBuffer scriptBuffer;
    unsigned scriptDataSize = source.readVLE();
    scriptBuffer.setData(source, scriptDataSize);
    if (mMethods[METHOD_LOAD])
    {
        std::vector<Variant> parameters;
        parameters.push_back(Variant((void*)static_cast<Deserializer*>(&scriptBuffer)));
        mScriptFile->execute(mScriptObject, mMethods[METHOD_LOAD], parameters);
    }
}

void ScriptInstance::postLoad(ResourceCache* cache)
{
    if (mMethods[METHOD_POSTLOAD])
        mScriptFile->execute(mScriptObject, mMethods[METHOD_POSTLOAD]);
}

void ScriptInstance::saveXML(XMLElement& dest)
{
    Component::saveXML(dest);
    
    XMLElement scriptElem = dest.createChildElement("script");
    scriptElem.setBool("enabled", mEnabled);
    scriptElem.setString("name", getResourceName(mScriptFile));
    scriptElem.setString("class", mClassName);
    
    if (mMethods[METHOD_SAVEXML])
    {
        XMLElement dataElem = dest.createChildElement("data");
        std::vector<Variant> parameters;
        parameters.push_back(Variant((void*)&dataElem));
        mScriptFile->execute(mScriptObject, mMethods[METHOD_SAVEXML], parameters);
    }
}

void ScriptInstance::loadXML(const XMLElement& source, ResourceCache* cache)
{
    Component::loadXML(source, cache);
    
    XMLElement scriptElem = source.getChildElement("script");
    mEnabled = scriptElem.getBool("enabled");
    setScriptClass(cache->getResource<ScriptFile>(scriptElem.getString("name")), scriptElem.getString("class"));
    
    if (mMethods[METHOD_LOADXML])
    {
        XMLElement dataElem = source.getChildElement("data");
        if (dataElem)
        {
            std::vector<Variant> parameters;
            parameters.push_back(Variant((void*)&dataElem));
            mScriptFile->execute(mScriptObject, mMethods[METHOD_LOADXML], parameters);
        }
    }
}

bool ScriptInstance::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    unsigned char bits = 0;
    StringHash scriptFileHash = getResourceHash(mScriptFile);
    checkBool(mEnabled, true, baseRevision, bits, 1);
    checkStringHash(scriptFileHash, StringHash(), baseRevision, bits, 2);
    checkString(mClassName, std::string(), baseRevision, bits, 2);
    
    // Save script's data into a separate buffer for safety
    static VectorBuffer scriptBuffer;
    scriptBuffer.clear();
    // Write update only if enabled
    if ((mEnabled) && (mMethods[METHOD_WRITENETUPDATE]))
    {
        std::vector<Variant> parameters;
        parameters.push_back(Variant((void*)static_cast<Serializer*>(&scriptBuffer)));
        parameters.push_back(Variant((void*)&info));
        mScriptFile->execute(mScriptObject, mMethods[METHOD_WRITENETUPDATE], parameters);
    }
    // Compare buffer to previous revision if available
    unsigned scriptDataSize = scriptBuffer.getSize();
    if (scriptDataSize)
        checkBuffer(scriptBuffer, baseRevision, bits, 4);
    
    dest.writeUByte(bits);
    writeBoolDelta(mEnabled, dest, destRevision, bits & 1);
    writeStringHashDelta(scriptFileHash, dest, destRevision, bits & 2);
    writeStringDelta(mClassName, dest, destRevision, bits & 2);
    writeBufferDelta(scriptBuffer, dest, destRevision, bits & 4);
    
    return bits != 0;
}

void ScriptInstance::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
{
    unsigned char bits = source.readUByte();
    if (bits & 1)
        mEnabled = source.readBool();
    if (bits & 2)
    {
        StringHash scriptFile = source.readStringHash();
        std::string className = source.readString();
        setScriptClass(cache->getResource<ScriptFile>(scriptFile), className);
    }
    if (bits & 4)
    {
        static VectorBuffer scriptBuffer;
        unsigned scriptDataSize = source.readVLE();
        scriptBuffer.setData(source, scriptDataSize);
        if (mMethods[METHOD_READNETUPDATE])
        {
            std::vector<Variant> parameters;
            parameters.push_back(Variant((void*)static_cast<Deserializer*>(&scriptBuffer)));
            parameters.push_back(Variant((void*)&info));
            mScriptFile->execute(mScriptObject, mMethods[METHOD_READNETUPDATE], parameters);
        }
    }
}

void ScriptInstance::postNetUpdate(ResourceCache* cache)
{
    if (mMethods[METHOD_POSTNETUPDATE])
        mScriptFile->execute(mScriptObject, mMethods[METHOD_POSTNETUPDATE]);
}

void ScriptInstance::interpolate(bool snapToEnd)
{
    if ((mEnabled) && (mMethods[METHOD_INTERPOLATE]))
    {
        std::vector<Variant> parameters;
        parameters.push_back(Variant(snapToEnd));
        mScriptFile->execute(mScriptObject, mMethods[METHOD_INTERPOLATE], parameters);
    }
}

void ScriptInstance::getComponentRefs(std::vector<ComponentRef>& dest)
{
    if ((mEnabled) && (mMethods[METHOD_GETCOMPONENTREFS]))
    {
        asIScriptContext* context = mScriptEngine->getScriptFileContext(getScriptNestingLevel());
        if (!context)
            return;
        mScriptFile->execute(mScriptObject, mMethods[METHOD_GETCOMPONENTREFS]);
        CScriptArray* arr = static_cast<CScriptArray*>(context->GetAddressOfReturnValue());
        if (arr)
        {
            for (unsigned i = 0; i < arr->GetSize(); ++i)
                dest.push_back(*(static_cast<ComponentRef*>(arr->At(i))));
        }
    }
}

void ScriptInstance::getResourceRefs(std::vector<Resource*>& dest)
{
    if (mMethods[METHOD_GETRESOURCEREFS])
    {
        asIScriptContext* context = mScriptEngine->getScriptFileContext(getScriptNestingLevel());
        if (!context)
            return;
        mScriptFile->execute(mScriptObject, mMethods[METHOD_GETRESOURCEREFS]);
        CScriptArray* arr = static_cast<CScriptArray*>(context->GetAddressOfReturnValue());
        if (arr)
        {
            for (unsigned i = 0; i < arr->GetSize(); ++i)
                dest.push_back(*(static_cast<Resource**>(arr->At(i))));
        }
    }
}

bool ScriptInstance::setScriptClass(ScriptFile* scriptFile, const std::string& className)
{
    if ((scriptFile == mScriptFile) && (className == mClassName))
        return true;
    
    releaseObject();
    
    mScriptFile = scriptFile;
    mClassName = className;
    
    if ((!mScriptFile) && (mClassName.empty()))
        return true;
    
    return createObject();
}

void ScriptInstance::setEnabled(bool enable)
{
    mEnabled = enable;
}

bool ScriptInstance::execute(const std::string& declaration, const std::vector<Variant>& parameters)
{
    if (!mScriptObject)
        return false;
    
    asIScriptFunction* method = mScriptFile->getMethod(mScriptObject, declaration);
    return mScriptFile->execute(mScriptObject, method, parameters);
}

bool ScriptInstance::execute(asIScriptFunction* method, const std::vector<Variant>& parameters)
{
    if ((!method) || (!mScriptObject))
        return false;
    
    return mScriptFile->execute(mScriptObject, method, parameters);
}

void ScriptInstance::addEventHandler(StringHash eventType, const std::string& handlerName)
{
    if (!mScriptObject)
        return;
    
    std::string declaration = "void " + handlerName + "(StringHash, VariantMap&)";
    asIScriptFunction* method = mScriptFile->getMethod(mScriptObject, declaration);
    if (!method)
    {
        LOGERROR("Event handler method " + declaration + " not found in " + mScriptFile->getName());
        return;
    }
    
    subscribeToEvent(eventType, EVENT_HANDLER(ScriptInstance, handleScriptEvent));
    mEventHandlers[eventType] = method;
}

bool ScriptInstance::createObject()
{
    if (!mScriptFile)
    {
        LOGERROR("Null script file for ScriptInstance");
        return false;
    }
    if (mClassName.empty())
    {
        LOGERROR("Empty script class name");
        return false;
    }
    
    mScriptObject = mScriptFile->createObject(mClassName);
    if (mScriptObject)
    {
        mScriptFile->addScriptInstance(this);
        objectToInstance[(void*)mScriptObject] = this;
        getSupportedMethods();
        if (mMethods[METHOD_START])
            mScriptFile->execute(mScriptObject, mMethods[METHOD_START]);
        return true;
    }
    else
    {
        LOGERROR("Failed to create object of class " + mClassName + " from " + mScriptFile->getName());
        return false;
    }
}

void ScriptInstance::releaseObject()
{
    if (mScriptObject)
    {
        if (mMethods[METHOD_STOP])
            mScriptFile->execute(mScriptObject, mMethods[METHOD_STOP]);
        
        removeAllEventHandlers();
        unsubscribeFromAllEvents();
        clearMethods();
        
        mScriptObject->Release();
        mScriptObject = 0;
        
        objectToInstance.erase((void*)mScriptObject);
        
        mScriptFile->removeScriptInstance(this);
    }
}

void ScriptInstance::clearMethods()
{
    for (unsigned i = 0; i < MAX_SCRIPT_METHODS; ++i)
        mMethods[i] = 0;
}

void ScriptInstance::getSupportedMethods()
{
    for (unsigned i = 0; i < MAX_SCRIPT_METHODS; ++i)
        mMethods[i] = mScriptFile->getMethod(mScriptObject, methodDeclarations[i]);
    
    // Subscribe to the update events as supported
    if (mMethods[METHOD_UPDATE])
        subscribeToEvent(EVENT_SCENEUPDATE, EVENT_HANDLER(ScriptInstance, handleSceneUpdate));
    if (mMethods[METHOD_POSTUPDATE])
        subscribeToEvent(EVENT_SCENEPOSTUPDATE, EVENT_HANDLER(ScriptInstance, handleScenePostUpdate));
    if (mMethods[METHOD_UPDATEFIXED])
        subscribeToEvent(EVENT_PHYSICSPRESTEP, EVENT_HANDLER(ScriptInstance, handlePhysicsPreStep));
    if (mMethods[METHOD_POSTUPDATEFIXED])
        subscribeToEvent(EVENT_PHYSICSPOSTSTEP, EVENT_HANDLER(ScriptInstance, handlePhysicsPostStep));
}

void ScriptInstance::handleSceneUpdate(StringHash eventType, VariantMap& eventData)
{
    if ((!mEnabled) || (!mScriptFile) || (!mScriptObject))
        return;
    
    using namespace SceneUpdate;
    
    // Check that the scene matches
    Scene* scene = mEntity ? mEntity->getScene() : 0;
    if (eventData[P_SCENE].getPtr() == (void*)scene)
    {
        std::vector<Variant> parameters;
        parameters.push_back(eventData[P_TIMESTEP]);
        mScriptFile->execute(mScriptObject, mMethods[METHOD_UPDATE], parameters);
    }
}

void ScriptInstance::handleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    if ((!mEnabled) || (!mScriptFile) || (!mScriptObject))
        return;
    
    using namespace ScenePostUpdate;
    
    // Check that the scene matches
    Scene* scene = mEntity ? mEntity->getScene() : 0;
    if (eventData[P_SCENE].getPtr() == (void*)scene)
    {
        std::vector<Variant> parameters;
        parameters.push_back(eventData[P_TIMESTEP]);
        mScriptFile->execute(mScriptObject, mMethods[METHOD_POSTUPDATE], parameters);
    }
}

void ScriptInstance::handlePhysicsPreStep(StringHash eventType, VariantMap& eventData)
{
    if ((!mEnabled) || (!mScriptFile) || (!mScriptObject))
        return;
    
    using namespace PhysicsPreStep;
    
    // Check that the scene matches
    Scene* scene = mEntity ? mEntity->getScene() : 0;
    if (eventData[P_SCENE].getPtr() == (void*)scene)
    {
        std::vector<Variant> parameters;
        parameters.push_back(eventData[P_TIMESTEP]);
        mScriptFile->execute(mScriptObject, mMethods[METHOD_UPDATEFIXED], parameters);
    }
}

void ScriptInstance::handlePhysicsPostStep(StringHash eventType, VariantMap& eventData)
{
    if ((!mEnabled) || (!mScriptFile) || (!mScriptObject))
        return;
    
    using namespace PhysicsPostStep;
    
    // Check that the scene matches
    Scene* scene = mEntity ? mEntity->getScene() : 0;
    if (eventData[P_SCENE].getPtr() == (void*)scene)
    {
        std::vector<Variant> parameters;
        parameters.push_back(eventData[P_TIMESTEP]);
        mScriptFile->execute(mScriptObject, mMethods[METHOD_POSTUPDATEFIXED], parameters);
    }
}

void ScriptInstance::handleScriptEvent(StringHash eventType, VariantMap& eventData)
{
    if ((!mEnabled) || (!mScriptFile) || (!mScriptObject))
        return;
    
    std::map<StringHash, asIScriptFunction*>::iterator i = mEventHandlers.find(eventType);
    if (i == mEventHandlers.end())
        return;
    
    std::vector<Variant> parameters;
    parameters.push_back(Variant((void*)&eventType));
    parameters.push_back(Variant((void*)&eventData));
    mScriptFile->execute(mScriptObject, i->second, parameters);
}

ScriptInstance* getScriptContextComponent()
{
    void* object = asGetActiveContext()->GetThisPointer();
    std::map<void*, ScriptInstance*>::const_iterator i = objectToInstance.find(object);
    if (i != objectToInstance.end())
        return i->second;
    else
        return 0;
}

Entity* getScriptContextEntity()
{
    ScriptInstance* instance = getScriptContextComponent();
    return instance ? instance->getEntity() : 0;
}
