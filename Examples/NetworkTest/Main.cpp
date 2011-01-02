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

#include "Exception.h"
#include "Log.h"
#include "Mutex.h"
#include "Network.h"
#include "Peer.h"
#include "ProcessUtils.h"
#include "Profiler.h"
#include "StringUtils.h"

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include "DebugNew.h"

int main(int argc, char** argv)
{
    std::vector<std::string> arguments;
    for (int i = 1; i < argc; ++i)
        arguments.push_back(std::string(argv[i]));
    
    if (arguments.size() < 1)
    {
        std::cout << "Usage (server): NetworkTest server\nUsage (client): NetworkTest <serveraddress> [username]" << std::endl;
        return 1;
    }
    
    Log log("NetworkTest.log", LOG_DEBUG);
    Network network;
    std::string userName;
    
    if (arguments[0] == "server")
    {
        if (!network.startServer(1234))
        {
            std::cout << "Failed to start server" << std::endl;
            return 1;
        }
    }
    else
    {
        if (arguments.size() > 1)
            userName = arguments[1];
        
        if (!network.connect(arguments[0], 1234))
        {
            std::cout << "Failed to connect" << std::endl;
            return 1;
        }
    }
    
    for (;;)
    {
        network.update();
        
        Peer* server = network.getServerPeer();
        // Client: check for server disconnection
        if ((!network.isServer()) && (!server))
            break;
        
        std::string command;
        if (getConsoleInput(command))
        {
            if (command == "shutdown")
                break;
            else
            {
                // Client: send the input in a packet, and optional username
                if (!network.isServer())
                {
                    VectorBuffer packet;
                    packet.writeString(command);
                    if (!userName.empty())
                        packet.writeString(userName);
                    server->send(packet, 0, true);
                }
            }
        }
        
        const std::vector<SharedPtr<Peer> >& peers = network.getPeers();
        for (unsigned i = 0; i < peers.size(); ++i)
        {
            VectorBuffer packet;
            while (peers[i]->receive(packet))
            {
                std::string message = packet.readString();
                // Server: broadcast the message to all, with the sender prepended, otherwise just show it
                if (network.isServer())
                {
                    // If packet contains also the username, show it, else just show IP and port
                    std::string name;
                    if (!packet.isEof())
                        name = packet.readString();
                    else
                        name = peers[i]->getAddress() + ":" + toString(peers[i]->getPort());
                    
                    std::string nameAndMessage = "[" + name + "] " + message;
                    
                    VectorBuffer newPacket;
                    newPacket.writeString(nameAndMessage);
                    network.broadcast(newPacket, 0, true);
                    
                    std::cout << nameAndMessage << std::endl;
                }
                else
                    std::cout << message << std::endl;
            }
        }
    }
    
    return 0;
}
