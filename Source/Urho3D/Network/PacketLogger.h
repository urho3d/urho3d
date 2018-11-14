//
//#pragma once
//#include <SLikeNet/PluginInterface2.h>
//#include "../IO/Log.h"
//#include "../Container/Str.h"
//
//using namespace Urho3D;
//
//class PacketLogger : public SLNet::PluginInterface2 {
//    /// OnReceive is called for every packet.
//    /// \param[in] packet the packet that is being returned to the user
//    /// \return True to allow the game and other plugins to get this message, false to absorb it
//    virtual SLNet::PluginReceiveResult OnReceive(SLNet::Packet *packet) {
//        counter++;
//        URHO3D_LOGINFO("Incoming packet!!!! " + String(counter));
//        (void) packet; return SLNet::RR_CONTINUE_PROCESSING;
//    }
//
//    unsigned int counter{};
//};
//
