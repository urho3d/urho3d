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

#ifndef ENGINE_SERVER_H
#define ENGINE_SERVER_H

#include "EventListener.h"
#include "Timer.h"
#include "SharedPtr.h"

#include <vector>

class Connection;
class Network;
class Scene;
class VectorBuffer;

//! Server-side ongoing download, with a timer for closing the file if unused
struct ServerFileTransfer
{
    SharedPtr<File> mFile;
    Timer mCloseTimer;
};

//! Provides scenes over the network
class Server : public RefCounted, public EventListener
{
public:
    //! Construct with network subsystem pointer
    Server(Network* network);
    //! Destruct
    virtual ~Server();
    
    //! Set network updates (number of server frames) per second
    void setNetFps(int fps);
    //! Set maximum unacked scene revisions stored per connection
    void setMaxSceneRevisions(int revisions);
    //! Set delay for entity becoming non-relevant, measured in server frames (prevent relevant/non-relevant state "flicker")
    void setStayRelevantTime(int time);
    //! Add a scene to be provided over the network
    void addScene(Scene* scene);
    //! Remove a scene
    void removeScene(Scene* scene);
    //! Start server in the specified port
    bool start(unsigned short port);
    //! Stop server
    void stop();
    //! Send and receive packets and update scene(s)
    void update(float timeStep);
    //! Assign client to a scene
    bool setClientScene(Connection* connection, Scene* scene);
    
    //! Return network updates per second
    int getNetFps() const { return mNetFps; }
    //! Return maximum unacked scene revisions stored per connection
    int getMaxSceneRevisions() const { return mMaxSceneRevisions; }
    //! Return delay for entity becoming non-relevant
    int getStayRelevantTime() const { return mStayRelevantTime; }
    //! Return whether is running on a port
    bool isRunning() const;
    //! Return whether has a specific scene
    bool hasScene(Scene* scene) const;
    //! Return all scenes
    const std::vector<SharedPtr<Scene> >& getScenes() const { return mScenes; }
    //! Return all connections
    const std::vector<SharedPtr<Connection> >& getConnections() const { return mConnections; }
    //! Return number of clients in scene
    unsigned getNumUsersInScene(Scene* scene) const;
    
private:
    //! Verify that the connection is valid
    Connection* verifyConnection(Connection* connection) const;
    //! Receive and handle packets from a connection
    void handlePackets(Connection* connection);
    //! Handle peer connected event
    void handlePeerConnected(StringHash eventType, VariantMap& eventData);
    //! Handle peer disconnected event
    void handlePeerDisconnected(StringHash eventType, VariantMap& eventData);
    //! Handle a reliable client packet
    bool handleReliablePacket(Connection* connection, VectorBuffer& packet);
    //! Handle an identity packet
    bool handleIdentity(Connection* connection, VectorBuffer& packet);
    //! Handle a file request packet
    bool handleRequestFile(Connection* connection, VectorBuffer& packet);
    //! Handle a join scene packet
    bool handleJoinScene(Connection* connection, VectorBuffer& packet);
    //! Handle a full update ack packet
    bool handleFullUpdateAck(Connection* connection, VectorBuffer& packet);
    //! Handle a client update packet
    bool handleClientUpdate(Connection* connection, VectorBuffer& packet);
    //! Check for new remote events queued in the scene(s)
    void checkRemoteEvents();
    //! Send scene info to the client
    void sendSceneInfo(Connection* connection);
    //! Send full scene update to the client
    void sendFullUpdate(Connection* connection);
    //! Send a scene update to the client
    void sendServerUpdate(Connection* connection);
    //! Generate a challenge value for the client
    unsigned generateChallenge() const;
    //! Disconnect client either forcibly or benevolently
    void disconnect(Connection* connection, bool forced, const std::string& logMessage);
    //! Generate a scene update. If connection has no stored scene revisions, a full update will be written
    void writeNetUpdate(Connection* connection, Serializer& dest);
    //! Return relevant entities for the client
    void getRelevantEntities(Connection* connection, std::set<EntityID>& dest) const;
    //! Return the entities a relevant entity depends on (and thus must also become relevant)
    void getEntityDependencies(Connection* connection, Entity* entity, std::set<EntityID>& dest) const;
    //! Return client-specific netflags for a component or entity, taking ownership into account
    unsigned char getClientNetFlags(Connection* connection, Entity* entity, unsigned char flags) const;
    
    //! Network subsystem
    SharedPtr<Network> mNetwork;
    //! Scenes
    std::vector<SharedPtr<Scene> > mScenes;
    //! Client connections
    std::vector<SharedPtr<Connection> > mConnections;
    //! Ongoing file downloads
    std::map<StringHash, ServerFileTransfer> mFileTransfers;
    //! Network updates per second
    int mNetFps;
    //! Network update time accumulator
    float mTimeAcc;
    //! Current server framenumber
    unsigned short mFrameNumber;
    //! Maximum scene revisions to store per connection
    unsigned mMaxSceneRevisions;
    //! Delay for entity becoming non-relevant, in server frames
    int mStayRelevantTime;
};

#endif // ENGINE_SERVER_H
