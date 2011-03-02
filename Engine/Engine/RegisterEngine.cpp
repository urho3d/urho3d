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
#include "AnimationController.h"
#include "Client.h"
#include "Console.h"
#include "Connection.h"
#include "DebugHud.h"
#include "ParticleEmitter.h"
#include "RegisterTemplates.h"
#include "Scene.h"
#include "ScriptInstance.h"
#include "Server.h"

static void SendRemoteEventToAll(const std::string& eventType, const VariantMap& eventData)
{
    Scene* scene = getScriptContextScene();
    if (scene)
        scene->sendRemoteEvent(StringHash(eventType), eventData);
}

static void SendRemoteEvent(const std::string& eventType, const VariantMap& eventData, Connection* receiver)
{
    Scene* scene = getScriptContextScene();
    if (scene)
        scene->sendRemoteEvent(StringHash(eventType), eventData, receiver);
}

static void SendRemoteEventTTL(const std::string& eventType, const VariantMap& eventData, Connection* receiver, unsigned short timeToLive)
{
    Scene* scene = getScriptContextScene();
    if (scene)
        scene->sendRemoteEvent(StringHash(eventType), eventData, receiver, timeToLive);
}

static void SendRemoteEntityEventToAll(Entity* entity, const std::string& eventType, const VariantMap& eventData)
{
    Scene* scene = getScriptContextScene();
    if (scene)
        scene->sendRemoteEvent(entity, StringHash(eventType), eventData);
}

static void SendRemoteEntityEvent(Entity* entity, const std::string& eventType, const VariantMap& eventData, Connection* receiver)
{
    Scene* scene = getScriptContextScene();
    if (scene)
        scene->sendRemoteEvent(entity, StringHash(eventType), eventData, receiver);
}

static void SendRemoteEntityEventTTL(Entity* entity, const std::string& eventType, const VariantMap& eventData, Connection* receiver, unsigned short timeToLive)
{
    Scene* scene = getScriptContextScene();
    if (scene)
        scene->sendRemoteEvent(entity, StringHash(eventType), eventData, receiver, timeToLive);
}

static void ConstructNetUpdateInfo(NetUpdateInfo* ptr)
{
    ptr->mConnection = 0;
    ptr->mFrameNumber = 0;
    ptr->mFrameAck = 0;
    ptr->mRemoteFrameNumber = 0;
    ptr->mRoundTripTime = 0.0f;
}

static Connection* NetUpdateInfoGetConnection(NetUpdateInfo* ptr)
{
    return ptr->mConnection;
}

static void registerConnection(asIScriptEngine* engine)
{
    engine->RegisterEnum("JoinState");
    engine->RegisterEnumValue("JoinState", "JS_NOTINSCENE", JS_NOTINSCENE);
    engine->RegisterEnumValue("JoinState", "JS_PREPARESCENE", JS_PREPARESCENE);
    engine->RegisterEnumValue("JoinState", "JS_SENDFULLUPDATE", JS_SENDFULLUPDATE);
    engine->RegisterEnumValue("JoinState", "JS_WAITFORACK", JS_WAITFORACK);
    engine->RegisterEnumValue("JoinState", "JS_SENDDELTAS", JS_SENDDELTAS);
    
    engine->RegisterObjectType("Connection", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Connection", asBEHAVE_ADDREF, "void f()", asMETHOD(Connection, addRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("Connection", asBEHAVE_RELEASE, "void f()", asMETHOD(Connection, releaseRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void disconnect()", asMETHOD(Connection, disconnect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void forceDisconnect()", asMETHOD(Connection, forceDisconnect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void setUserName(const string& in)", asMETHOD(Connection, setUserName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void setControls(const Controls& in)", asMETHOD(Connection, setControls), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "Scene@+ getScene() const", asMETHOD(Connection, getScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const string& getUserName() const", asMETHOD(Connection, getUserName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool isConnected() const", asMETHOD(Connection, isConnected), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "JoinState getJoinState() const", asMETHOD(Connection, getJoinState), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "uint16 getFrameNumber() const", asMETHOD(Connection, getFrameNumber), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "uint16 getFrameAck() const", asMETHOD(Connection, getFrameAck), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "float getRoundTripTime() const", asMETHOD(Connection, getRoundTripTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const Controls& getControls() const", asMETHOD(Connection, getControls), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const Vector3& getPosition() const", asMETHOD(Connection, getPosition), asCALL_THISCALL);
    registerRefCasts<EventListener, Connection>(engine, "EventListener", "Connection");
    
    // Register Variant getPtr() for Connection
    engine->RegisterObjectMethod("Variant", "Connection@+ getConnection() const", asFUNCTION(getVariantPtr<Connection>), asCALL_CDECL_OBJLAST);
    
    engine->RegisterObjectType("NetUpdateInfo", sizeof(NetUpdateInfo), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("NetUpdateInfo", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructNetUpdateInfo), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("NetUpdateInfo", "Connection@+ get_connection() const", asFUNCTION(NetUpdateInfoGetConnection), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("NetUpdateInfo", "uint16 frameNumber", offsetof(NetUpdateInfo, mFrameNumber));
    engine->RegisterObjectProperty("NetUpdateInfo", "uint16 frameAck", offsetof(NetUpdateInfo, mFrameAck));
    engine->RegisterObjectProperty("NetUpdateInfo", "uint16 remoteFrameNumber", offsetof(NetUpdateInfo, mRemoteFrameNumber));
    engine->RegisterObjectProperty("NetUpdateInfo", "float roundTripTime", offsetof(NetUpdateInfo, mRoundTripTime));
    
    // Add missing Scene & Entity methods that have to do with Connection
    engine->RegisterObjectMethod("Scene", "void resetOwner(Connection@+)", asMETHOD(Scene, resetOwner), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "bool checkSync(Connection@+) const", asMETHOD(Entity, checkSync), asCALL_THISCALL);
    engine->RegisterObjectMethod("Entity", "bool checkPrediction(Connection@+) const", asMETHOD(Entity, checkPrediction), asCALL_THISCALL);
    
    // Add remote event functionality as global functions because the Scene can be found out through the context
    engine->RegisterGlobalFunction("void sendRemoteEvent(const string& in, const VariantMap& in)", asFUNCTION(SendRemoteEventToAll), asCALL_CDECL);
    engine->RegisterGlobalFunction("void sendRemoteEvent(const string& in, const VariantMap& in, Connection@+)", asFUNCTION(SendRemoteEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void sendRemoteEvent(const string& in, const VariantMap& in, Connection@+, uint16)", asFUNCTION(SendRemoteEventTTL), asCALL_CDECL);
    engine->RegisterGlobalFunction("void sendRemoteEvent(Entity@+, const string& in, const VariantMap& in)", asFUNCTION(SendRemoteEntityEventToAll), asCALL_CDECL);
    engine->RegisterGlobalFunction("void sendRemoteEvent(Entity@+, const string& in, const VariantMap& in, Connection@+)", asFUNCTION(SendRemoteEntityEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void sendRemoteEvent(Entity@+, const string& in, const VariantMap& in, Connection@+, uint16)", asFUNCTION(SendRemoteEntityEventTTL), asCALL_CDECL);
    engine->RegisterGlobalFunction("void registerRemoteEvent(const string& in)", asFUNCTIONPR(registerRemoteEvent, (const std::string&), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void unregisterRemoteEvent(const string& in)", asFUNCTIONPR(unregisterRemoteEvent, (const std::string&), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void unregisterAllRemoteEvents()", asFUNCTION(unregisterAllRemoteEvents), asCALL_CDECL);
    engine->RegisterGlobalFunction("Connection@+ getRemoteEventSender()", asFUNCTION(getRemoteEventSender), asCALL_CDECL);
}

static void ConstructSceneInfo(SceneInfo* ptr)
{
    new(ptr) SceneInfo();
}

static void ConstructSceneInfoCopy(const SceneInfo& info, SceneInfo* ptr)
{
    new(ptr) SceneInfo(info);
}

static void DestructSceneInfo(SceneInfo* ptr)
{
    ptr->~SceneInfo();
}

static bool ClientConnectAddress(const std::string& address, unsigned short port, Client* ptr)
{
    return ptr->connect(address, port);
}

static bool ClientConnectAddressUserName(const std::string& address, unsigned short port, const std::string& userName, Client* ptr)
{
    return ptr->connect(address, port, userName);
}

static Client* GetClient()
{
    return getEngine()->getClient();
}

static bool IsClient()
{
    return GetClient() != 0;
}

static const std::string& SceneInfoGetName(SceneInfo* ptr)
{
    return ptr->mName;
}

static unsigned SceneInfoGetNumUsers(SceneInfo* ptr)
{
    return ptr->mNumUsers;
}

static int SceneInfoGetNetFps(SceneInfo* ptr)
{
    return ptr->mNetFps;
}

static const std::string& SceneInfoGetFileName(SceneInfo* ptr)
{
    return ptr->mFileName;
}

static void registerClient(asIScriptEngine* engine)
{
    engine->RegisterObjectType("SceneInfo", sizeof(SceneInfo), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
    engine->RegisterObjectBehaviour("SceneInfo", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructSceneInfo), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("SceneInfo", asBEHAVE_CONSTRUCT, "void f(const SceneInfo& in)", asFUNCTION(ConstructSceneInfoCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("SceneInfo", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructSceneInfo), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("SceneInfo", "SceneInfo &opAssign(const SceneInfo& in)", asMETHOD(SceneInfo, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("SceneInfo", "const string& get_name() const", asFUNCTION(SceneInfoGetName), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("SceneInfo", "uint get_numUsers() const", asFUNCTION(SceneInfoGetNumUsers), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("SceneInfo", "int get_netFps() const", asFUNCTION(SceneInfoGetNetFps), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("SceneInfo", "const string& get_fileName() const", asFUNCTION(SceneInfoGetFileName), asCALL_CDECL_OBJLAST);
    
    engine->RegisterObjectType("Client", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Client", asBEHAVE_ADDREF, "void f()", asMETHOD(Client, addRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("Client", asBEHAVE_RELEASE, "void f()", asMETHOD(Client, releaseRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("Client", "void setScene(Scene@+)", asMETHOD(Client, setScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("Client", "void setMaxPredictionTime(float)", asMETHOD(Client, setMaxPredictionTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("Client", "bool connect(const string& in, uint16)", asFUNCTION(ClientConnectAddress), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Client", "bool connect(const string& in, uint16, const string& in)", asFUNCTION(ClientConnectAddressUserName), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Client", "bool connect(const string& in, uint16, const string& in, const VariantMap& in)", asMETHOD(Client, connect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Client", "void disconnect()", asMETHOD(Client, disconnect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Client", "void setControls(const Controls& in)", asMETHOD(Client, setControls), asCALL_THISCALL);
    engine->RegisterObjectMethod("Client", "void setPosition(const Vector3& in)", asMETHOD(Client, setPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Client", "Scene@+ getScene() const", asMETHOD(Client, getScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("Client", "Connection@+ getServerConnection() const", asMETHOD(Client, getServerConnection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Client", "bool isConnected() const", asMETHOD(Client, isConnected), asCALL_THISCALL);
    engine->RegisterObjectMethod("Client", "bool isJoinPending() const", asMETHOD(Client, isJoinPending), asCALL_THISCALL);
    engine->RegisterObjectMethod("Client", "bool isJoined() const", asMETHOD(Client, isJoined), asCALL_THISCALL);
    engine->RegisterObjectMethod("Client", "int getNetFps() const", asMETHOD(Client, getNetFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Client", "float getMaxPredictionTime() const", asMETHOD(Client, getMaxPredictionTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("Client", "const Controls& getControls() const", asMETHOD(Client, getControls), asCALL_THISCALL);
    engine->RegisterObjectMethod("Client", "const Vector3& getPosition() const", asMETHOD(Client, getPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Client", "uint getNumFileTransfers() const", asMETHOD(Client, getNumFileTransfers), asCALL_THISCALL);
    engine->RegisterObjectMethod("Client", "const string& getDownloadDirectory() const", asMETHOD(Client, getDownloadDirectory), asCALL_THISCALL);
    engine->RegisterObjectMethod("Client", "string getFileTransferStatus() const", asMETHOD(Client, getFileTransferStatus), asCALL_THISCALL);
    engine->RegisterObjectMethod("Client", "const SceneInfo& getSceneInfo() const", asMETHOD(Client, getSceneInfo), asCALL_THISCALL);
    registerRefCasts<EventListener, Client>(engine, "EventListener", "Client");
    
    engine->RegisterGlobalFunction("Client@+ getClient()", asFUNCTION(GetClient), asCALL_CDECL);
    engine->RegisterGlobalFunction("Client@+ get_client()", asFUNCTION(GetClient), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool isClient()", asFUNCTION(IsClient), asCALL_CDECL);
}

static CScriptArray* ServerGetScenes(Server* ptr)
{
    const std::vector<SharedPtr<Scene> >& scenes = ptr->getScenes();
    return sharedPtrVectorToHandleArray<Scene>(scenes, "array<Scene@>");
}

static CScriptArray* ServerGetConnections(Server* ptr)
{
    const std::vector<SharedPtr<Connection> >& connections = ptr->getConnections();
    return sharedPtrVectorToHandleArray<Connection>(connections, "array<Connection@>");
}

static Server* GetServer()
{
    return getEngine()->getServer();
}

static bool IsServer()
{
    return GetServer() != 0;
}

static void registerServer(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Server", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Server", asBEHAVE_ADDREF, "void f()", asMETHOD(Server, addRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("Server", asBEHAVE_RELEASE, "void f()", asMETHOD(Server, releaseRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("Server", "void setNetFps(int)", asMETHOD(Server, setNetFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Server", "void setMaxSceneRevisions(int)", asMETHOD(Server, setMaxSceneRevisions), asCALL_THISCALL);
    engine->RegisterObjectMethod("Server", "void setStayRelevantTime(int)", asMETHOD(Server, setStayRelevantTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("Server", "void addScene(Scene@+)", asMETHOD(Server, addScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("Server", "void removeScene(Scene@+)", asMETHOD(Server, removeScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("Server", "bool start(uint16)", asMETHOD(Server, start), asCALL_THISCALL);
    engine->RegisterObjectMethod("Server", "void stop()", asMETHOD(Server, stop), asCALL_THISCALL);
    engine->RegisterObjectMethod("Server", "bool setClientScene(Connection@+, Scene@+)", asMETHOD(Server, setClientScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("Server", "int getNetFps() const", asMETHOD(Server, getNetFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Server", "int getMaxSceneRevisions() const", asMETHOD(Server, getMaxSceneRevisions), asCALL_THISCALL);
    engine->RegisterObjectMethod("Server", "int getStayRelevantTime() const", asMETHOD(Server, getStayRelevantTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("Server", "bool isRunning() const", asMETHOD(Server, isRunning), asCALL_THISCALL);
    engine->RegisterObjectMethod("Server", "bool hasScene(Scene@+) const", asMETHOD(Server, hasScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("Server", "array<Scene@>@ getScenes() const", asFUNCTION(ServerGetScenes), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Server", "array<Connection@>@ getConnections() const", asFUNCTION(ServerGetConnections), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Server", "uint getNumUsersInScene(Scene@+) const", asMETHOD(Server, getNumUsersInScene), asCALL_THISCALL);
    registerRefCasts<EventListener, Server>(engine, "EventListener", "Server");
    
    engine->RegisterGlobalFunction("Server@+ getServer()", asFUNCTION(GetServer), asCALL_CDECL);
    engine->RegisterGlobalFunction("Server@+ get_server()", asFUNCTION(GetServer), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool isServer()", asFUNCTION(IsServer), asCALL_CDECL);
}

static void ParticleEmitterLoadParameters(XMLFile* file, ParticleEmitter* ptr)
{
    ptr->loadParameters(file, getEngine()->getResourceCache());
}

static void registerAnimationController(asIScriptEngine* engine)
{
    registerComponent<AnimationController>(engine, "AnimationController");
    engine->RegisterObjectMethod("AnimationController", "void setAnimatedModel(AnimatedModel@+)", asMETHOD(AnimationController, setAnimatedModel), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool addAnimation(const string& in, uint8)", asMETHOD(AnimationController, addAnimation), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool removeAnimation(const string& in, float)", asMETHOD(AnimationController, removeAnimation), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "void removeAnimations(uint8, float)", asMETHOD(AnimationController, removeAnimations), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "void removeAllAnimations(float)", asMETHOD(AnimationController, removeAllAnimations), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool setAnimation(const string& in, uint8, bool, bool, float, float, float, float, bool)", asMETHOD(AnimationController, setAnimation), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool setProperties(const string& in, uint8, float, float, float, float)", asMETHOD(AnimationController, setProperties), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool setPriority(const string& in, int)", asMETHOD(AnimationController, setPriority), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool setStartBone(const string& in, const string& in)", asMETHOD(AnimationController, setStartBone), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool setBlending(const string& in, int, const string& in)", asMETHOD(AnimationController, setBlending), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool setTime(const string& in, float)", asMETHOD(AnimationController, setTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool setWeight(const string& in, float)", asMETHOD(AnimationController, setWeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool setLooped(const string& in, bool)", asMETHOD(AnimationController, setLooped), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool setGroup(const string& in, uint8)", asMETHOD(AnimationController, setGroup), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool setSpeed(const string& in, float)", asMETHOD(AnimationController, setSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool setFade(const string& in, float, float)", asMETHOD(AnimationController, setFade), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool setFadeOthers(const string& in, float, float)", asMETHOD(AnimationController, setFadeOthers), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool setAutoFade(const string& in, float)", asMETHOD(AnimationController, setAutoFade), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "AnimatedModel@+ getAnimatedModel() const", asMETHOD(AnimationController, getAnimatedModel), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool hasAnimation(const string& in) const", asMETHOD(AnimationController, hasAnimation), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "int getPriority(const string& in) const", asMETHOD(AnimationController, getPriority), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "Bone@+ getStartBone(const string& in) const", asMETHOD(AnimationController, getStartBone), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "float getTime(const string& in) const", asMETHOD(AnimationController, getTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "float getWeight(const string& in) const", asMETHOD(AnimationController, getWeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool isLooped(const string& in) const", asMETHOD(AnimationController, isLooped), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "float getLength(const string& in) const", asMETHOD(AnimationController, getLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "uint8 getGroup(const string& in) const", asMETHOD(AnimationController, getGroup), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "float getSpeed(const string& in) const", asMETHOD(AnimationController, getSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "float getFadeTarget(const string& in) const", asMETHOD(AnimationController, getFadeTarget), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "float getAutoFade(const string& in) const", asMETHOD(AnimationController, getAutoFade), asCALL_THISCALL);
    registerRefCasts<Component, AnimationController>(engine, "Component", "AnimationController");
}

static void registerParticleEmitter(asIScriptEngine* engine)
{
    registerGeometryNode<ParticleEmitter>(engine, "ParticleEmitter");
    engine->RegisterObjectMethod("ParticleEmitter", "void setMaterial(Material@+)", asMETHODPR(ParticleEmitter, setMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void setBillboardsRelative(bool)", asMETHODPR(ParticleEmitter, setBillboardsRelative, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void setBillboardsSorted(bool)", asMETHODPR(ParticleEmitter, setBillboardsSorted, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void setScaleBillboards(bool)", asMETHODPR(ParticleEmitter, setScaleBillboards, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void setAnimationLodBias(float)", asMETHODPR(ParticleEmitter, setAnimationLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "Material@+ getMaterial() const", asMETHODPR(ParticleEmitter, getMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool getBillboardsRelative() const", asMETHODPR(ParticleEmitter, getBillboardsRelative, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool getBillboardsSorted() const", asMETHODPR(ParticleEmitter, getBillboardsSorted, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool getScaleBillboards() const", asMETHODPR(ParticleEmitter, getScaleBillboards, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "float getAnimationLodBias() const", asMETHODPR(ParticleEmitter, getAnimationLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void loadParameters(XMLFile@+ file)", asFUNCTION(ParticleEmitterLoadParameters), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ParticleEmitter", "void setActive(bool, bool)", asMETHOD(ParticleEmitter, setActive), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "XMLFile@+ getParameters() const", asMETHOD(ParticleEmitter, getParameters), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool isActive() const", asMETHOD(ParticleEmitter, isActive), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint getNumParticles() const", asMETHOD(ParticleEmitter, getNumParticles), asCALL_THISCALL);
    registerRefCasts<Component, ParticleEmitter>(engine, "Component", "ParticleEmitter");
    registerRefCasts<Node, ParticleEmitter>(engine, "Node", "ParticleEmitter");
}

static Console* GetConsole()
{
    return getEngine()->getConsole();
}

static void registerConsole(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Console", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Console", asBEHAVE_ADDREF, "void f()", asMETHOD(Console, addRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("Console", asBEHAVE_RELEASE, "void f()", asMETHOD(Console, releaseRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void setStyle(XMLFile@+ file)", asMETHOD(Console, setStyle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void setVisible(bool)", asMETHOD(Console, setVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void toggle()", asMETHOD(Console, toggle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void setNumRows(uint)", asMETHOD(Console, setNumRows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void setNumHistoryRows(uint)", asMETHOD(Console, setNumHistoryRows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void updateElements()", asMETHOD(Console, updateElements), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "XMLFile@+ getStyle() const", asMETHOD(Console, getStyle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "BorderImage@+ getBackground() const", asMETHOD(Console, getBackground), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "LineEdit@+ getLineEdit() const", asMETHOD(Console, getLineEdit), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "bool isVisible() const", asMETHOD(Console, isVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "uint getNumRows() const", asMETHOD(Console, getNumRows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "uint getNumHistoryRows() const", asMETHOD(Console, getNumHistoryRows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "uint getHistoryPosition() const", asMETHOD(Console, getHistoryPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "const string& getHistoryRow(uint) const", asMETHOD(Console, getHistoryRow), asCALL_THISCALL);
    engine->RegisterGlobalFunction("Console@+ getConsole()", asFUNCTION(GetConsole), asCALL_CDECL);
    engine->RegisterGlobalFunction("Console@+ get_console()", asFUNCTION(GetConsole), asCALL_CDECL);
}

static DebugHud* GetDebugHud()
{
    return getEngine()->getDebugHud();
}

static void registerDebugHud(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("const uint DEBUGHUD_SHOW_NONE", (void*)&DEBUGHUD_SHOW_NONE);
    engine->RegisterGlobalProperty("const uint DEBUGHUD_SHOW_STATS", (void*)&DEBUGHUD_SHOW_STATS);
    engine->RegisterGlobalProperty("const uint DEBUGHUD_SHOW_MODE", (void*)&DEBUGHUD_SHOW_MODE);
    engine->RegisterGlobalProperty("const uint DEBUGHUD_SHOW_PROFILER", (void*)&DEBUGHUD_SHOW_PROFILER);
    
    engine->RegisterObjectType("DebugHud", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("DebugHud", asBEHAVE_ADDREF, "void f()", asMETHOD(DebugHud, addRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("DebugHud", asBEHAVE_RELEASE, "void f()", asMETHOD(DebugHud, releaseRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void setStyle(XMLFile@+)", asMETHOD(DebugHud, setStyle), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void setMode(uint)", asMETHOD(DebugHud, setMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void setProfilerInterval(float)", asMETHOD(DebugHud, setProfilerInterval), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void toggle(uint)", asMETHOD(DebugHud, toggle), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void toggleAll()", asMETHOD(DebugHud, toggleAll), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "XMLFile@+ getStyle() const", asMETHOD(DebugHud, getStyle), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "Text@+ getStatsText() const", asMETHOD(DebugHud, getStatsText), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "Text@+ getModeText() const", asMETHOD(DebugHud, getModeText), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "Text@+ getProfilerText() const", asMETHOD(DebugHud, getProfilerText), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "uint getMode() const", asMETHOD(DebugHud, getMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "float getProfilerInterval() const", asMETHOD(DebugHud, getProfilerInterval), asCALL_THISCALL);
    
    engine->RegisterGlobalFunction("DebugHud@+ getDebugHud()", asFUNCTION(GetDebugHud), asCALL_CDECL);
    engine->RegisterGlobalFunction("DebugHud@+ get_debugHud()", asFUNCTION(GetDebugHud), asCALL_CDECL);
}

static Scene* EngineCreateScene(const std::string& name, const BoundingBox& octreeSize, unsigned octreeLevels, bool usePhysics, Engine* ptr)
{
    SharedPtr<Scene> newScene = ptr->createScene(name, octreeSize, octreeLevels, usePhysics);
    // The shared pointer will go out of scope, so have to increment the reference count
    // (here an auto handle can not be used)
    newScene->addRef();
    return newScene.getPtr();
}

static void registerEngine(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Engine", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Engine", asBEHAVE_ADDREF, "void f()", asMETHOD(Engine, addRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("Engine", asBEHAVE_RELEASE, "void f()", asMETHOD(Engine, releaseRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void runFrame()", asMETHOD(Engine, runFrame), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "Scene@ createScene(const string& in, const BoundingBox& in, uint, bool)", asFUNCTION(EngineCreateScene), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Engine", "Client@+ createClient(const string& in)", asMETHOD(Engine, createClient), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "Server@+ createServer()", asMETHOD(Engine, createServer), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "Console@+ createConsole()", asMETHOD(Engine, createConsole), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "DebugHud@+ createDebugHud()", asMETHOD(Engine, createDebugHud), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void removeClient()", asMETHOD(Engine, removeClient), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void removeServer()", asMETHOD(Engine, removeServer), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void setDefaultScene(Scene@+)", asMETHOD(Engine, setDefaultScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void setDefaultScriptFile(ScriptFile@+)", asMETHOD(Engine, setDefaultScriptFile), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void setMinFps(int)", asMETHOD(Engine, setMinFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void setMaxFps(int)", asMETHOD(Engine, setMaxFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void setMaxInactiveFps(int)", asMETHOD(Engine, setMaxInactiveFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void setFlushGPU(bool)", asMETHOD(Engine, setFlushGPU), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void exit()", asMETHOD(Engine, exit), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void dumpProfilingData()", asMETHOD(Engine, dumpProfilingData), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void dumpResources()", asMETHOD(Engine, dumpResources), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "Scene@+ getDefaultScene() const", asMETHOD(Engine, getDefaultScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "int getMinFps() const", asMETHOD(Engine, getMinFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "int getMaxFps() const", asMETHOD(Engine, getMaxFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "int getMaxInactiveFps() const", asMETHOD(Engine, getMaxInactiveFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "bool getFlushGPU() const", asMETHOD(Engine, getFlushGPU), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "bool isInitialized() const", asMETHOD(Engine, isInitialized), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "bool isExiting() const", asMETHOD(Engine, isExiting), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "bool isHeadless() const", asMETHOD(Engine, isHeadless), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "float getNextTimeStep()", asMETHOD(Engine, getNextTimeStep), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void update(float, Scene@+, Camera@+, bool)", asMETHOD(Engine, update), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void render()", asMETHOD(Engine, render), asCALL_THISCALL);
    engine->RegisterGlobalFunction("Engine@+ getEngine()", asFUNCTION(getEngine), asCALL_CDECL);
    engine->RegisterGlobalFunction("Engine@+ get_engine()", asFUNCTION(getEngine), asCALL_CDECL);
    registerRefCasts<EventListener, Engine>(engine, "EventListener", "Engine");
}

void registerEngineLibrary(asIScriptEngine* engine)
{
    registerConnection(engine);
    registerClient(engine);
    registerServer(engine);
    registerAnimationController(engine);
    registerParticleEmitter(engine);
    registerConsole(engine);
    registerDebugHud(engine);
    registerEngine(engine);
}
