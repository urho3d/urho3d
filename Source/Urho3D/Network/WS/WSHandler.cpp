#include "WSHandler.h"
#include "../../IO/Log.h"
#include <libwebsockets.h>

using namespace Urho3D;

WSHandler::WSHandler(Urho3D::Network *networkInstance):
    networkInstance_(networkInstance)
{

}

WSHandler::~WSHandler()
{

}

void WSHandler::AddIncomingPacket(const WSPacket& packet)
{
    Urho3D::MutexLock lock(GetIncomingMutex());
    incomingPackets_.Push(packet);
}

WSPacket& WSHandler::GetIncomingPacket()
{
    return incomingPackets_.Front();
}

void WSHandler::RemoveIncomingPacket()
{
    if (GetNumIncomingPackets() > 0) {
        Urho3D::MutexLock lock(GetIncomingMutex());
        incomingPackets_.Front().second_.Clear();
        incomingPackets_.PopFront();
    }
}

void WSHandler::AddOutgoingPacket(const WSPacket& packet)
{
    Urho3D::MutexLock lock(GetOutgoingMutex());
    outgoingPackets_.Push(packet);
}

WSPacket& WSHandler::GetOutgoingPacket()
{
    return outgoingPackets_.Front();
}

void WSHandler::RemoveOutgoingPacket()
{
    if (GetNumOutgoingPackets() > 0) {
        Urho3D::MutexLock lock(GetOutgoingMutex());
        outgoingPackets_.Front().second_.Clear();
        outgoingPackets_.PopFront();
    }
}

void WSHandler::OutputWSLog(int level, const char *line)
{
    switch(level) {
        case LLL_NOTICE:
            URHO3D_LOGINFOF("WSClient: %s", line);
            break;
        case LLL_WARN:
            URHO3D_LOGWARNINGF("WSClient: %s", line);
            break;
        case LLL_ERR:
            URHO3D_LOGERRORF("WSClient: %s", line);
            break;
        case LLL_USER:
            URHO3D_LOGINFOF("WSClient: %s", line);
            break;
    }
}