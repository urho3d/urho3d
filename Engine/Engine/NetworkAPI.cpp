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
#include "Peer.h"

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

void RegisterPeer(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("const uint8 CHANNEL_ANY", (void*)&CHANNEL_ANY);
    
    engine->RegisterEnum("PeerType");
    engine->RegisterEnumValue("PeerType", "PEER_SERVER", PEER_SERVER);
    engine->RegisterEnumValue("PeerType", "PEER_CLIENT", PEER_CLIENT);
    
    engine->RegisterEnum("ConnectionState");
    engine->RegisterEnumValue("ConnectionState", "CS_DISCONNECTED", CS_DISCONNECTED);
    engine->RegisterEnumValue("ConnectionState", "CS_DISCONNECTING", CS_DISCONNECTING);
    engine->RegisterEnumValue("ConnectionState", "CS_CONNECTING", CS_CONNECTING);
    engine->RegisterEnumValue("ConnectionState", "CS_CONNECTED", CS_CONNECTED);
    
    RegisterObject<Peer>(engine, "Peer");
    engine->RegisterObjectMethod("Peer", "void Send(const VectorBuffer&in, uint8, bool, bool)", asMETHODPR(Peer, Send, (const VectorBuffer&, unsigned char, bool, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Peer", "bool Receive(VectorBuffer&, uint8)", asMETHOD(Peer, Receive), asCALL_THISCALL);
    engine->RegisterObjectMethod("Peer", "void FlushPackets()", asMETHOD(Peer, FlushPackets), asCALL_THISCALL);
    engine->RegisterObjectMethod("Peer", "bool HasPackets() const", asMETHOD(Peer, HasPackets), asCALL_THISCALL);
    engine->RegisterObjectMethod("Peer", "void Disconnect()", asMETHOD(Peer, Disconnect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Peer", "void ForceDisconnect()", asMETHOD(Peer, ForceDisconnect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Peer", "void set_simulatedPacketLoss(float)", asMETHOD(Peer, SetSimulatedPacketLoss), asCALL_THISCALL);
    engine->RegisterObjectMethod("Peer", "float get_simulatedPacketLoss() const", asMETHOD(Peer, GetSimulatedPacketLoss), asCALL_THISCALL);
    engine->RegisterObjectMethod("Peer", "void set_simulatedLatency(uint)", asMETHOD(Peer, SetSimulatedLatency), asCALL_THISCALL);
    engine->RegisterObjectMethod("Peer", "uint get_simulatedLatency() const" ,asMETHOD(Peer, GetSimulatedLatency), asCALL_THISCALL);
    engine->RegisterObjectMethod("Peer", "PeerType get_peerType() const", asMETHOD(Peer, GetPeerType), asCALL_THISCALL),
    engine->RegisterObjectMethod("Peer", "ConnectionState get_connectionState() const", asMETHOD(Peer, GetConnectionState), asCALL_THISCALL);
    engine->RegisterObjectMethod("Peer", "uint get_numPackets() const", asMETHOD(Peer, GetNumPackets), asCALL_THISCALL);
    engine->RegisterObjectMethod("Peer", "const String& get_address() const", asMETHOD(Peer, GetAddress), asCALL_THISCALL);
    engine->RegisterObjectMethod("Peer", "uint16 get_port() const", asMETHOD(Peer, GetPort), asCALL_THISCALL);
    
    // Register Variant GetPtr() for Peer
    engine->RegisterObjectMethod("Variant", "Peer@+ GetPeer() const", asFUNCTION(GetVariantPtr<Peer>), asCALL_CDECL_OBJLAST);
}

static Network* GetNetwork()
{
    return GetScriptContext()->GetSubsystem<Network>();
}

void RegisterNetwork(asIScriptEngine* engine)
{
    RegisterObject<Network>(engine, "Network");
    engine->RegisterObjectMethod("Network", "void SetDataRate(int, int)", asMETHOD(Network, SetDataRate), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "bool StartServer(uint16)", asMETHOD(Network, StartServer), asCALL_THISCALL),
    engine->RegisterObjectMethod("Network", "Peer@+ Connect(const String&in, uint16)", asMETHOD(Network, Connect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void StopServer()", asMETHOD(Network, StopServer), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void StopClient()", asMETHOD(Network, StopClient), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void Broadcast(const VectorBuffer&in, uint8, bool, bool)", asMETHODPR(Network, Broadcast, (const VectorBuffer&, unsigned char, bool ,bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void set_serverMaxConnections(uint)", asMETHOD(Network, SetServerMaxConnections), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "uint get_serverMaxConnections() const", asMETHOD(Network, GetServerMaxConnections), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void set_clientMaxConnections(uint)", asMETHOD(Network, SetClientMaxConnections), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "uint get_clientMaxConnections() const", asMETHOD(Network, GetClientMaxConnections), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void set_numChannels(uint)", asMETHOD(Network, SetNumChannels), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "uint get_numChannels() const", asMETHOD(Network, GetNumChannels), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "bool get_serverStarted() const", asMETHOD(Network, IsServer), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "bool get_clientStarted() const", asMETHOD(Network, IsClient), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "uint get_numPeers() const", asMETHOD(Network, GetNumPeers), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "int get_dataRateIn() const", asMETHOD(Network, GetDataRateIn), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "int get_dataRateOut() const", asMETHOD(Network, GetDataRateOut), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "Peer@+ get_peers(uint) const", asMETHOD(Network, GetPeer), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "Peer@+ get_serverPeer() const", asMETHOD(Network, GetServerPeer), asCALL_THISCALL);
    engine->RegisterGlobalFunction("Network@+ get_network()", asFUNCTION(GetNetwork), asCALL_CDECL);
}

void RegisterNetworkAPI(asIScriptEngine* engine)
{
    RegisterControls(engine);
    RegisterPeer(engine);
    RegisterNetwork(engine);
}
