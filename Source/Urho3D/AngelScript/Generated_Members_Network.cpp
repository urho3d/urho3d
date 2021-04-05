// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/GeneratedClassMembers.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

#ifdef URHO3D_NETWORK

// struct PackageDownload | File: ../Network/Connection.h
void CollectMembers_PackageDownload(MemberCollection& members)
{
    // SharedPtr<File> PackageDownload::file_
    // Error: type "SharedPtr<File>" can not automatically bind
    // HashSet<unsigned> PackageDownload::receivedFragments_
    // Error: type "HashSet<unsigned>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("String PackageDownload::name_", "String name", offsetof(PackageDownload, name_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned PackageDownload::totalFragments_", "uint totalFragments", offsetof(PackageDownload, totalFragments_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned PackageDownload::checksum_", "uint checksum", offsetof(PackageDownload, checksum_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool PackageDownload::initiated_", "bool initiated", offsetof(PackageDownload, initiated_)));

}

// struct PackageUpload | File: ../Network/Connection.h
void CollectMembers_PackageUpload(MemberCollection& members)
{
    // SharedPtr<File> PackageUpload::file_
    // Error: type "SharedPtr<File>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("unsigned PackageUpload::fragment_", "uint fragment", offsetof(PackageUpload, fragment_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned PackageUpload::totalFragments_", "uint totalFragments", offsetof(PackageUpload, totalFragments_)));

}

// struct RemoteEvent | File: ../Network/Connection.h
void CollectMembers_RemoteEvent(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned RemoteEvent::senderID_", "uint senderID", offsetof(RemoteEvent, senderID_)));
    members.fields_.Push(RegisterObjectPropertyArgs("StringHash RemoteEvent::eventType_", "StringHash eventType", offsetof(RemoteEvent, eventType_)));
    members.fields_.Push(RegisterObjectPropertyArgs("VariantMap RemoteEvent::eventData_", "VariantMap eventData", offsetof(RemoteEvent, eventData_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool RemoteEvent::inOrder_", "bool inOrder", offsetof(RemoteEvent, inOrder_)));

}

// class HttpRequest | File: ../Network/HttpRequest.h
void CollectMembers_HttpRequest(MemberCollection& members)
{
    CollectMembers_RefCounted(members);
    CollectMembers_Deserializer(members);
    CollectMembers_Thread(members);

    Remove(members.methods_, "virtual bool Deserializer::IsEof() const");
    Remove(members.methods_, "virtual unsigned Deserializer::Read(void* dest, unsigned size) = 0");
    Remove(members.methods_, "virtual unsigned Deserializer::Seek(unsigned position) = 0");
    Remove(members.methods_, "virtual void Thread::ThreadFunction() = 0");

}

// class Connection | File: ../Network/Connection.h
void CollectMembers_Connection(MemberCollection& members)
{
    CollectMembers_Object(members);

    // const SLNet::AddressOrGUID& Connection::GetAddressOrGUID() const
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind
    // bool Connection::ProcessMessage(int msgID, MemoryBuffer& buffer)
    // Error: type "MemoryBuffer" can not automatically bind bacause have @nobind mark
    // void Connection::SendMessage(int msgID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes, unsigned contentID = 0)
    // Error: type "const unsigned char*" can not automatically bind
    // void Connection::SetAddressOrGUID(const SLNet::AddressOrGUID& addr)
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("Controls Connection::controls_", "Controls controls", offsetof(Connection, controls_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned char Connection::timeStamp_", "uint8 timeStamp", offsetof(Connection, timeStamp_)));
    members.fields_.Push(RegisterObjectPropertyArgs("VariantMap Connection::identity_", "VariantMap identity", offsetof(Connection, identity_)));

}

// class Network | File: ../Network/Network.h
void CollectMembers_Network(MemberCollection& members)
{
    CollectMembers_Object(members);

    // void Network::BroadcastMessage(int msgID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes, unsigned contentID = 0)
    // Error: type "const unsigned char*" can not automatically bind
    // void Network::ClientDisconnected(const SLNet::AddressOrGUID& connection)
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind
    // Connection* Network::GetConnection(const SLNet::AddressOrGUID& connection) const
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind
    // void Network::HandleMessage(const SLNet::AddressOrGUID& source, int packetID, int msgID, const char* data, size_t numBytes)
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind
    // void Network::NewConnectionEstablished(const SLNet::AddressOrGUID& connection)
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind

}

// class NetworkPriority | File: ../Network/NetworkPriority.h
void CollectMembers_NetworkPriority(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

}

#endif // def URHO3D_NETWORK

} // namespace Urho3D
