//
// Copyright (c) 2008-2014 the Urho3D project.
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

#ifdef URHO3D_NETWORK
#include "../Script/APITemplates.h"
#include "../Network/Controls.h"
#include "../Network/HttpRequest.h"
#include "../Network/Network.h"
#include "../Network/NetworkPriority.h"
#include "../Network/Protocol.h"

namespace Urho3D
{

static void ConstructControls(Controls* ptr)
{
    new(ptr) Controls();
}

static void ConstructControlsCopy(const Controls& controls, Controls* ptr)
{
    new(ptr) Controls(controls);
}

static void DestructControls(Controls* ptr)
{
    ptr->~Controls();
}

static void RegisterControls(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Controls", sizeof(Controls), asOBJ_VALUE | asOBJ_APP_CLASS_CDK);
    engine->RegisterObjectBehaviour("Controls", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructControls), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Controls", asBEHAVE_CONSTRUCT, "void f(const Controls&in)", asFUNCTION(ConstructControlsCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Controls", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructControls), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Controls", "Controls& opAssign(const Controls&in)", asMETHOD(Controls, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "void Reset()", asMETHOD(Controls, Reset), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "void Set(uint, bool)", asMETHOD(Controls, Set), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "bool IsDown(uint) const", asMETHOD(Controls, IsDown), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "bool IsPressed(uint, const Controls&in) const", asMETHOD(Controls, IsPressed), asCALL_THISCALL);
    engine->RegisterObjectProperty("Controls", "uint buttons", offsetof(Controls, buttons_));
    engine->RegisterObjectProperty("Controls", "float yaw", offsetof(Controls, yaw_));
    engine->RegisterObjectProperty("Controls", "float pitch", offsetof(Controls, pitch_));
    engine->RegisterObjectProperty("Controls", "VariantMap extraData", offsetof(Controls, extraData_));
}

static void RegisterNetworkPriority(asIScriptEngine* engine)
{
    RegisterComponent<NetworkPriority>(engine, "NetworkPriority");
    engine->RegisterObjectMethod("NetworkPriority", "void set_basePriority(float)", asMETHOD(NetworkPriority, SetBasePriority), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "float get_basePriority() const", asMETHOD(NetworkPriority, GetBasePriority), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_distanceFactor(float)", asMETHOD(NetworkPriority, SetDistanceFactor), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "float get_distanceFactor() const", asMETHOD(NetworkPriority, GetDistanceFactor), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_minPriority(float)", asMETHOD(NetworkPriority, SetMinPriority), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "float get_minPriority() const", asMETHOD(NetworkPriority, GetMinPriority), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_alwaysUpdateOwner(bool)", asMETHOD(NetworkPriority, SetAlwaysUpdateOwner), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "bool get_alwaysUpdateOwner() const", asMETHOD(NetworkPriority, GetAlwaysUpdateOwner), asCALL_THISCALL);
}

void SendRemoteEvent(const String& eventType, bool inOrder, const VariantMap& eventData, Connection* ptr)
{
    ptr->SendRemoteEvent(eventType, inOrder, eventData);
}

void SendRemoteNodeEvent(Node* receiver, const String& eventType, bool inOrder, const VariantMap& eventData, Connection* ptr)
{
    ptr->SendRemoteEvent(receiver, eventType, inOrder, eventData);
}

static void RegisterConnection(asIScriptEngine* engine)
{
    RegisterObject<Connection>(engine, "Connection");
    engine->RegisterObjectMethod("Connection", "void SendMessage(int, bool, bool, const VectorBuffer&in, uint contentID = 0)", asMETHODPR(Connection, SendMessage, (int, bool, bool, const VectorBuffer&, unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void SendRemoteEvent(const String&in, bool, const VariantMap&in eventData = VariantMap())", asFUNCTION(SendRemoteEvent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Connection", "void SendRemoteEvent(Node@+, const String&in, bool, const VariantMap&in eventData = VariantMap())", asFUNCTION(SendRemoteNodeEvent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Connection", "void Disconnect(int waitMSec = 0)", asMETHOD(Connection, Disconnect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "String ToString() const", asMETHOD(Connection, ToString), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void set_scene(Scene@+)", asMETHOD(Connection, SetScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "Scene@+ get_scene() const", asMETHOD(Connection, GetScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void set_logStatistics(bool)", asMETHOD(Connection, SetLogStatistics), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool get_logStatistics() const", asMETHOD(Connection, GetLogStatistics), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool get_client() const", asMETHOD(Connection, IsClient), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool get_connected() const", asMETHOD(Connection, IsConnected), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool get_connectPending() const", asMETHOD(Connection, IsConnectPending), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool get_sceneLoaded() const", asMETHOD(Connection, IsSceneLoaded), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "String get_address() const", asMETHOD(Connection, GetAddress), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "uint16 get_port() const", asMETHOD(Connection, GetPort), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "uint get_numDownloads() const", asMETHOD(Connection, GetNumDownloads), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const String& get_downloadName() const", asMETHOD(Connection, GetDownloadName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "float get_downloadProgress() const", asMETHOD(Connection, GetDownloadProgress), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void set_position(const Vector3&in)", asMETHOD(Connection, SetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const Vector3& get_position() const", asMETHOD(Connection, GetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void set_rotation(const Quaternion&in)", asMETHOD(Connection, SetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const Quaternion& get_rotation() const", asMETHOD(Connection, GetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void SendPackageToClient(PackageFile@+)", asMETHOD(Connection, SendPackageToClient), asCALL_THISCALL);
    engine->RegisterObjectProperty("Connection", "Controls controls", offsetof(Connection, controls_));
    engine->RegisterObjectProperty("Connection", "VariantMap identity", offsetof(Connection, identity_));
    
    // Register SetOwner/GetOwner now
    engine->RegisterObjectMethod("Node", "void set_owner(Connection@+)", asMETHOD(Node, SetOwner), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Connection@+ get_owner() const", asMETHOD(Node, GetOwner), asCALL_THISCALL);
}

static void RegisterHttpRequest(asIScriptEngine* engine)
{
    engine->RegisterEnum("HttpRequestState");
    engine->RegisterEnumValue("HttpRequestState", "HTTP_INITIALIZING", HTTP_INITIALIZING);
    engine->RegisterEnumValue("HttpRequestState", "HTTP_ERROR", HTTP_ERROR);
    engine->RegisterEnumValue("HttpRequestState", "HTTP_OPEN", HTTP_OPEN);
    engine->RegisterEnumValue("HttpRequestState", "HTTP_CLOSED", HTTP_CLOSED);
    
    RegisterRefCounted<HttpRequest>(engine, "HttpRequest");
    RegisterDeserializer<HttpRequest>(engine, "HttpRequest");
    engine->RegisterObjectMethod("HttpRequest", "const String& get_url() const", asMETHOD(HttpRequest, GetURL), asCALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "const String& get_verb() const", asMETHOD(HttpRequest, GetVerb), asCALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "String get_error() const", asMETHOD(HttpRequest, GetError), asCALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "HttpRequestState get_state() const", asMETHOD(HttpRequest, GetState), asCALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "uint get_availableSize() const", asMETHOD(HttpRequest, GetAvailableSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "bool get_open() const", asMETHOD(HttpRequest, IsOpen), asCALL_THISCALL);
}

static Network* GetNetwork()
{
    return GetScriptContext()->GetSubsystem<Network>();
}

static CScriptArray* NetworkGetClientConnections(Network* ptr)
{
    const Vector<SharedPtr<Connection> >& connections = ptr->GetClientConnections();
    return VectorToHandleArray(connections, "Array<Connection@>");
}

static void NetworkBroadcastRemoteEvent(const String& eventType, bool inOrder, const VariantMap& eventData, Network* ptr)
{
    ptr->BroadcastRemoteEvent(eventType, inOrder, eventData);
}

static void NetworkBroadcastRemoteSceneEvent(Scene* scene, const String& eventType, bool inOrder, const VariantMap& eventData, Network* ptr)
{
    ptr->BroadcastRemoteEvent(scene, eventType, inOrder, eventData);
}

static void NetworkBroadcastRemoteNodeEvent(Node* node, const String& eventType, bool inOrder, const VariantMap& eventData, Network* ptr)
{
    ptr->BroadcastRemoteEvent(node, eventType, inOrder, eventData);
}

static void NetworkRegisterRemoteEvent(const String& eventType, Network* ptr)
{
    ptr->RegisterRemoteEvent(eventType);
}

static void NetworkUnregisterRemoteEvent(const String& eventType, Network* ptr)
{
    ptr->UnregisterRemoteEvent(eventType);
}

static bool NetworkCheckRemoteEvent(const String& eventType, Network* ptr)
{
    return ptr->CheckRemoteEvent(eventType);
}

static HttpRequest* NetworkMakeHttpRequest(const String& url, const String& verb, CScriptArray* headers, const String& postData, Network* ptr)
{
    SharedPtr<HttpRequest> request = ptr->MakeHttpRequest(url, verb, ArrayToVector<String>(headers), postData);
    // The shared pointer will go out of scope, so have to increment the reference count
    // (here an auto handle can not be used)
    if (request)
        request->AddRef();
    return request.Get();
}

void RegisterNetwork(asIScriptEngine* engine)
{
    RegisterObject<Network>(engine, "Network");
    engine->RegisterObjectMethod("Network", "bool Connect(const String&in, uint16, Scene@+, const VariantMap&in identity = VariantMap())", asMETHOD(Network, Connect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void Disconnect(int waitMSec = 0)", asMETHOD(Network, Disconnect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "bool StartServer(uint16)", asMETHOD(Network, StartServer), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void StopServer()", asMETHOD(Network, StopServer), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void BroadcastMessage(int, bool, bool, const VectorBuffer&in, uint contentID = 0)", asMETHODPR(Network, BroadcastMessage, (int, bool, bool, const VectorBuffer&, unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void BroadcastRemoteEvent(const String&in, bool, const VariantMap&in eventData = VariantMap())", asFUNCTION(NetworkBroadcastRemoteEvent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Network", "void BroadcastRemoteEvent(Scene@+, const String&in, bool, const VariantMap&in eventData = VariantMap())", asFUNCTION(NetworkBroadcastRemoteSceneEvent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Network", "void BroadcastRemoteEvent(Node@+, const String&in, bool, const VariantMap&in eventData = VariantMap())", asFUNCTION(NetworkBroadcastRemoteNodeEvent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Network", "void RegisterRemoteEvent(const String&in) const", asFUNCTION(NetworkRegisterRemoteEvent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Network", "void UnregisterRemoteEvent(const String&in) const", asFUNCTION(NetworkUnregisterRemoteEvent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Network", "void UnregisterAllRemoteEvents()", asMETHOD(Network, UnregisterAllRemoteEvents), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "bool CheckRemoteEvent(const String&in) const", asFUNCTION(NetworkCheckRemoteEvent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Network", "HttpRequest@ MakeHttpRequest(const String&in, const String&in verb = String(), Array<String>@+ headers = null, const String&in postData = String())", asFUNCTION(NetworkMakeHttpRequest), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Network", "void SendPackageToClients(Scene@+, PackageFile@+)", asMETHOD(Network, SendPackageToClients), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void set_updateFps(int)", asMETHOD(Network, SetUpdateFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "int get_updateFps() const", asMETHOD(Network, GetUpdateFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void set_packageCacheDir(const String&in)", asMETHOD(Network, SetPackageCacheDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "const String& get_packageCacheDir() const", asMETHOD(Network, GetPackageCacheDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "bool get_serverRunning() const", asMETHOD(Network, IsServerRunning), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "Connection@+ get_serverConnection() const", asMETHOD(Network, GetServerConnection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "Array<Connection@>@ get_clientConnections() const", asFUNCTION(NetworkGetClientConnections), asCALL_CDECL_OBJLAST);
    engine->RegisterGlobalFunction("Network@+ get_network()", asFUNCTION(GetNetwork), asCALL_CDECL);
}

void RegisterNetworkAPI(asIScriptEngine* engine)
{
    RegisterControls(engine);
    RegisterNetworkPriority(engine);
    RegisterConnection(engine);
    RegisterHttpRequest(engine);
    RegisterNetwork(engine);
}

}

#endif
