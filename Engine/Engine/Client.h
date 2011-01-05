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

#ifndef ENGINE_CLIENT_H
#define ENGINE_CLIENT_H

#include "Component.h"
#include "Controls.h"
#include "EventListener.h"
#include "File.h"
#include "SharedPtr.h"
#include "Timer.h"
#include "VectorBuffer.h"

#include <map>
#include <set>

class Connection;
class Network;
class ResourceCache;
class Scene;

//! Downloadable package file description
struct PackageInfo
{
    //! File name
    std::string mName;
    //! File size
    unsigned mSize;
    //! Data checksum
    unsigned mChecksum;
};

//! Server scene description
struct SceneInfo
{
    //! Construct with default values
    SceneInfo() :
        mNumUsers(0),
        mNetFps(0)
    {
    }
    
    //! Scene name
    std::string mName;
    //! Current number of users in scene
    unsigned mNumUsers;
    //! Network updates per second
    int mNetFps;
    //! Scene file name
    std::string mFileName;
    //! Required package files
    std::vector<PackageInfo> mRequiredPackages;
    //! Scene and scene extension properties serialized in a buffer
    VectorBuffer mSceneProperties;
};

//! An ongoing download from the server
struct FileTransfer
{
    //! Construct with default values
    FileTransfer() :
        mNumReceived(0),
        mBytesReceived(0),
        mBatchStart(0),
        mBatchSize(0),
        mLastBatchSize(0),
        mLastDataRate(0.0f)
    {
    }
    
    //! File used to store the download
    SharedPtr<File> mFile;
    //! File name
    std::string mFileName;
    //! File size
    unsigned mSize;
    //! Data checksum
    unsigned mChecksum;
    //! Total number of fragments
    unsigned mNumFragments;
    //! Fragments received so far
    unsigned mNumReceived;
    //! Bytes received so far
    unsigned mBytesReceived;
    //! Timer for current batch of fragments
    Timer mBatchTimer;
    //! Timer for the whole transfer
    Timer mReceiveTimer;
    //! First fragment number in the current batch
    unsigned mBatchStart;
    //! Number of fragments in the current batch
    unsigned mBatchSize;
    //! Number of fragments in the previous batch
    unsigned mLastBatchSize;
    //! Download rate of the previous batch
    float mLastDataRate;
};

//! Receives scene updates over the network
class Client : public RefCounted, public EventListener
{
public:
    //! Construct with pointers to the network subsystem and resource cache and the directory to use for download
    Client(Network* network, ResourceCache* cache, const std::string& downloadDirectory);
    //! Destruct
    virtual ~Client();
    
    //! Set scene to use. Will be cleared of any existing content
    void setScene(Scene* scene);
    //! Set maximum amount of client-side prediction
    void setMaxPredictionTime(float time);
    //! Connect to a server
    bool connect(const std::string& address, unsigned short port, const std::string& userName = std::string(), const VariantMap&
        loginData = VariantMap());
    //! Disconnect from a server
    void disconnect();
    //! Set client controls to be sent over the network
    void setControls(const Controls& controls);
    //! Set client position to be sent over the network for entity relevancy calculations
    void setPosition(const Vector3& position);
    //! Send and receive packets and update the scene
    void update(float timeStep);
    
    //! Return the scene
    Scene* getScene() const { return mScene; }
    //! Return the server connection
    Connection* getServerConnection() const { return mServerConnection; }
    //! Return whether connected
    bool isConnected() const;
    //! Return whether scene join pending
    bool isJoinPending() const;
    //! Return whether joined a scene
    bool isJoined() const;
    //! Return network updates per second
    int getNetFps() const { return mNetFps; }
    //! Return maximum client-side prediction time
    float getMaxPredictionTime() const { return mMaxPredictionTime; }
    //! Return client frame number
    unsigned short getFrameNumber() const { return mFrameNumber; }
    //! Return client controls
    const Controls& getControls() const;
    //! Return client position
    const Vector3& getPosition() const;
    //! Return scene info
    const SceneInfo& getSceneInfo() const { return mSceneInfo; }
    //! Return number of ongoing file transfers
    unsigned getNumFileTransfers() { return mFileTransfers.size(); }
    //! Return ongoing file transfers
    const std::map<StringHash, FileTransfer>& getFileTransfers() { return mFileTransfers; }
    //! Return download directory
    const std::string& getDownloadDirectory() const { return mDownloadDirectory; }
    //! Return file transfer status as text
    std::string getFileTransferStatus() const;
    
private:
    //! Handle network peer disconnect event
    void handlePeerDisconnected(StringHash eventType, VariantMap& eventData);
    //! Handle file transfer complete event
    void handleFileTransferCompleted(StringHash eventType, VariantMap& eventData);
    //! Handle file transfer failed event
    void handleFileTransferFailed(StringHash eventType, VariantMap& eventData);
    //! Handle async scene loading finished event
    void handleAsyncLoadFinished(StringHash eventType, VariantMap& eventData);
    //! Handle a reliable network packet
    void handleReliablePacket(VectorBuffer& packet);
    //! Handle a challenge packet
    void handleChallenge(VectorBuffer& packet);
    //! Handle a scene info packet
    void handleSceneInfo(VectorBuffer& packet);
    //! Handle a file transfer packet
    void handleTransferData(VectorBuffer& packet);
    //! Handle a file transfer failed packet
    void handleTransferFailed(VectorBuffer& packet);
    //! Handle a join reply packet
    void handleJoinReply(VectorBuffer& packet);
    //! Handle a full scene update from the server
    void handleFullUpdate(VectorBuffer& packet);
    //! Handle a server update packet
    void handleServerUpdate(VectorBuffer& packet, bool initial = false);
    //! Replay controls for client-side prediction
    void replayControls();
    //! Check whether packages need to be downloaded to join the scene
    unsigned checkPackages();
    //! Begin a file download
    bool requestFile(const std::string& fileName, unsigned size, unsigned checksum);
    //! Begin setup of the client scene
    void setupScene();
    //! Send join scene packet after scene setup is complete
    void sendJoinScene();
    //! Send join failed event
    void joinFailed(const std::string& reason);
    //! Send a client update packet
    void sendClientUpdate();
    //! Read a server update block
    void readNetUpdateBlock(Deserializer& source, unsigned char msgID, const NetUpdateInfo& info,
        std::set<EntityID>& updatedEntities);
    
    //! Network subsystem
    SharedPtr<Network> mNetwork;
    //! Resource cache
    SharedPtr<ResourceCache> mCache;
    //! Scene
    SharedPtr<Scene> mScene;
    //! Server connection
    SharedPtr<Connection> mServerConnection;
    //! Network updates per second
    int mNetFps;
    //! Network update time accumulator
    float mTimeAcc;
    //! Maximum client-side prediction time
    float mMaxPredictionTime;
    //! Client framenumber
    unsigned short mFrameNumber;
    //! Scene info
    SceneInfo mSceneInfo;
    //! Ongoing file downloads
    std::map<StringHash, FileTransfer> mFileTransfers;
    //! Directory to use for downloads
    std::string mDownloadDirectory;
    //! Downloads required to join the scene
    std::set<std::string> mPendingDownloads;
    //! Username to send to the server
    std::string mPendingUserName;
    //! Extra login data to send to the server
    VariantMap mPendingLoginData;
};

//! Return Client instance
Client* getClient();

#endif // ENGINE_CLIENT_H
