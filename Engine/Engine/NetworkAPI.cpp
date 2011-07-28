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
#include "APITemplates.h"
#include "Controls.h"
#include "Network.h"
#include "Protocol.h"

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
    engine->RegisterObjectType("Controls", sizeof(Controls), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
    engine->RegisterObjectBehaviour("Controls", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructControls), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Controls", asBEHAVE_CONSTRUCT, "void f(const Controls&in)", asFUNCTION(ConstructControlsCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Controls", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructControls), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Controls", "Controls &opAssign(const Controls&in)", asMETHOD(Controls, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "void Reset()", asMETHOD(Controls, Reset), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "void Set(uint, bool)", asMETHOD(Controls, Set), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "bool IsDown(uint)", asMETHOD(Controls, IsDown), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "bool IsPressed(uint, const Controls&in)", asMETHOD(Controls, IsPressed), asCALL_THISCALL);
    engine->RegisterObjectProperty("Controls", "uint buttons", offsetof(Controls, buttons_));
    engine->RegisterObjectProperty("Controls", "float yaw", offsetof(Controls, yaw_));
    engine->RegisterObjectProperty("Controls", "float pitch", offsetof(Controls, pitch_));
    engine->RegisterObjectProperty("Controls", "VariantMap extraData", offsetof(Controls, extraData_));
}

void SendRemoteEvent(const String& eventType, bool inOrder, const VariantMap& eventData, Connection* ptr)
{
    ptr->SendRemoteEvent(StringHash(eventType), inOrder, eventData);
}

void SendRemoteNodeEvent(Node* receiver, const String& eventType, bool inOrder, const VariantMap& eventData, Connection* ptr)
{
    ptr->SendRemoteEvent(receiver, StringHash(eventType), inOrder, eventData);
}

static void RegisterConnection(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("uint NET_LOW_PRIORITY", (void*)&NET_LOW_PRIORITY);
    engine->RegisterGlobalProperty("uint NET_MEDIUM_PRIORITY", (void*)&NET_MEDIUM_PRIORITY);
    engine->RegisterGlobalProperty("uint NET_HIGH_PRIORITY", (void*)&NET_HIGH_PRIORITY);
    
    RegisterObject<Connection>(engine, "Connection");
    engine->RegisterObjectMethod("Connection", "void SendMessage(int, bool, bool, const VectorBuffer&in, uint priority = 0, uint contentID = 0)", asMETHODPR(Connection, SendMessage, (int, bool, bool, const VectorBuffer&, unsigned, unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void SendRemoteEvent(const String&in, bool, const VariantMap&in eventData = VariantMap())", asFUNCTION(SendRemoteEvent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Connection", "void SendRemoteEvent(Node@+, const String&in, bool, const VariantMap&in eventData = VariantMap())", asFUNCTION(SendRemoteNodeEvent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Connection", "void Disconnect(int waitMSec = 0)", asMETHOD(Connection, Disconnect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "String ToString() const", asMETHOD(Connection, ToString), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void set_scene(Scene@+)", asMETHOD(Connection, SetScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "Scene@+ get_scene() const", asMETHOD(Connection, GetScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool get_client() const", asMETHOD(Connection, IsClient), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool get_connected() const", asMETHOD(Connection, IsConnected), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool get_connectPending() const", asMETHOD(Connection, IsConnectPending), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool get_sceneLoaded() const", asMETHOD(Connection, IsSceneLoaded), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "String get_address() const", asMETHOD(Connection, GetAddress), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "uint16 get_port() const", asMETHOD(Connection, GetPort), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "uint get_numDownloads() const", asMETHOD(Connection, GetNumDownloads), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const String& get_downloadName() const", asMETHOD(Connection, GetDownloadName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "float get_downloadProgress() const", asMETHOD(Connection, GetDownloadProgress), asCALL_THISCALL);
    
    // Register Variant GetPtr() for Connection
    engine->RegisterObjectMethod("Variant", "Connection@+ GetConnection() const", asFUNCTION(GetVariantPtr<Connection>), asCALL_CDECL_OBJLAST);
}

static Network* GetNetwork()
{
    return GetScriptContext()->GetSubsystem<Network>();
}

static CScriptArray* NetworkGetClientConnections(Network* ptr)
{
    const Map<kNet::MessageConnection*, SharedPtr<Connection> >& connections = ptr->GetClientConnections();
    
    asIScriptContext *context = asGetActiveContext();
    if (context)
    {
        asIObjectType* type = GetScriptContext()->GetSubsystem<Script>()->GetObjectType("Array<Connection@>");
        CScriptArray* arr = new CScriptArray(connections.Size(), type);
        
        unsigned index = 0;
        for (Map<kNet::MessageConnection*, SharedPtr<Connection> >::ConstIterator i = connections.Begin();
            i != connections.End(); ++i)
        {
            // Increment reference count for storing in the array
            Connection* connection = i->second_;
            if (connection)
                connection->AddRef();
            *(static_cast<Connection**>(arr->At(index))) = connection;
            ++index;
        }
        
        return arr;
    }
    else
        return 0;
}

static void NetworkBroadcastRemoteEvent(const String& eventType, bool inOrder, const VariantMap& eventData, Network* ptr)
{
    ptr->BroadcastRemoteEvent(StringHash(eventType), inOrder, eventData);
}

static void NetworkBroadcastRemoteSceneEvent(Scene* scene, const String& eventType, bool inOrder, const VariantMap& eventData, Network* ptr)
{
    ptr->BroadcastRemoteEvent(scene, StringHash(eventType), inOrder, eventData);
}

static void NetworkBroadcastRemoteNodeEvent(Node* node, const String& eventType, bool inOrder, const VariantMap& eventData, Network* ptr)
{
    ptr->BroadcastRemoteEvent(node, StringHash(eventType), inOrder, eventData);
}

static void NetworkRegisterRemoteEvent(const String& eventType, Network* ptr)
{
    ptr->RegisterRemoteEvent(StringHash(eventType));
}

static void NetworkUnregisterRemoteEvent(const String& eventType, Network* ptr)
{
    ptr->UnregisterRemoteEvent(StringHash(eventType));
}

static bool NetworkCheckRemoteEvent(const String& eventType, Network* ptr)
{
    return ptr->CheckRemoteEvent(StringHash(eventType));
}

void RegisterNetwork(asIScriptEngine* engine)
{
    RegisterObject<Network>(engine, "Network");
    engine->RegisterObjectMethod("Network", "bool Connect(const String&in, uint16, Scene@+, const VariantMap&in identity = VariantMap())", asMETHOD(Network, Connect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void Disconnect(int waitMSec = 0)", asMETHOD(Network, Disconnect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "bool StartServer(uint16)", asMETHOD(Network, StartServer), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void StopServer()", asMETHOD(Network, StopServer), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void BroadcastMessage(int, bool, bool, const VectorBuffer&in, uint priority = 0, uint contentID = 0)", asMETHODPR(Network, BroadcastMessage, (int, bool, bool, const VectorBuffer&, unsigned, unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void BroadcastRemoteEvent(const String&in, bool, const VariantMap&in eventData = VariantMap())", asFUNCTION(NetworkBroadcastRemoteEvent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Network", "void BroadcastRemoteEvent(Scene@+, const String&in, bool, const VariantMap&in eventData = VariantMap())", asFUNCTION(NetworkBroadcastRemoteSceneEvent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Network", "void BroadcastRemoteEvent(Node@+, const String&in, bool, const VariantMap&in eventData = VariantMap())", asFUNCTION(NetworkBroadcastRemoteNodeEvent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Network", "void RegisterRemoteEvent(const String&in) const", asFUNCTION(NetworkRegisterRemoteEvent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Network", "void UnregisterRemoteEvent(const String&in) const", asFUNCTION(NetworkUnregisterRemoteEvent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Network", "void UnregisterAllRemoteEvents()", asMETHOD(Network, UnregisterAllRemoteEvents), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "bool CheckRemoteEvent(const String&in) const", asFUNCTION(NetworkCheckRemoteEvent), asCALL_CDECL_OBJLAST);
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
    RegisterConnection(engine);
    RegisterNetwork(engine);
}
