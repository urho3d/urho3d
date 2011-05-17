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

#pragma once

#include "Controls.h"
#include "File.h"
#include "Object.h"
#include "Timer.h"
#include "VectorBuffer.h"

#include <map>
#include <set>

class Connection;
class Network;
class ResourceCache;
class Scene;

/// Downloadable package file description
struct PackageInfo
{
    /// File name
    String name_;
    /// File size
    unsigned size_;
    /// Data checksum
    unsigned checksum_;
};

/// Server scene description
struct SceneInfo
{
    /// Construct with default values
    SceneInfo() :
        numUsers_(0),
        netFps_(0)
    {
    }
    
    /// Scene name
    String name_;
    /// Current number of users in scene
    unsigned numUsers_;
    /// Network updates per second
    int netFps_;
    /// Scene file name
    String fileName_;
    /// Required package files
    std::vector<PackageInfo> requiredPackages_;
};

/// An ongoing download from the server
struct FileTransfer
{
    /// Construct with default values
    FileTransfer() :
        fragmentsReceived_(0),
        bytesReceived_(0),
        batchStart_(0),
        batchSize_(0),
        lastBatchSize_(0),
        lastDataRate_(0.0f)
    {
    }
    
    /// File used to store the download
    SharedPtr<File> file_;
    /// File name
    String fileName_;
    /// File size
    unsigned size_;
    /// Data checksum
    unsigned checksum_;
    /// Total number of fragments
    unsigned numFragments_;
    /// Fragments received so far
    unsigned fragmentsReceived_;
    /// Bytes received so far
    unsigned bytesReceived_;
    /// Timer for current batch of fragments
    Timer batchTimer_;
    /// Timer for the whole transfer
    Timer receiveTimer_;
    /// First fragment number in the current batch
    unsigned batchStart_;
    /// Number of fragments in the current batch
    unsigned batchSize_;
    /// Number of fragments in the previous batch
    unsigned lastBatchSize_;
    /// Download rate of the previous batch
    float lastDataRate_;
};

/// Multiplayer client subsystem
class Client : public Object
{
    OBJECT(Object);
    
public:
    /// Construct
    Client(Context* context);
    /// Destruct
    virtual ~Client();
    
    /// Set scene to use. Will be cleared of any existing content
    void SetScene(Scene* scene);
    /// Set package download directory
    void SetDownloadDirectory(const String& path);
    /// Connect to a server
    bool Connect(const String& address, unsigned short port, const VariantMap& loginData = VariantMap());
    /// Disconnect from a server
    void Disconnect();
    /// Set client controls to be sent over the network
    void SetControls(const Controls& controls);
    /// Set client position to be sent over the network for node relevancy calculations
    void SetPosition(const Vector3& position);
    /// Send and receive packets and update the scene
    void Update(float timeStep);
    
    /// Return the scene
    Scene* GetScene() const { return scene_; }
    /// Return the server connection
    Connection* GetServerConnection() const { return serverConnection_; }
    /// Return whether connected
    bool IsConnected() const;
    /// Return whether scene join pending
    bool IsJoinPending() const;
    /// Return whether joined a scene
    bool IsJoined() const;
    /// Return network updates per second
    int GetNetFps() const { return netFps_; }
    /// Return client frame number
    unsigned short GetFrameNumber() const { return frameNumber_; }
    /// Return client controls
    const Controls& GetControls() const;
    /// Return client position
    const Vector3& GetPosition() const;
    /// Return scene info
    const SceneInfo& GetSceneInfo() const { return sceneInfo_; }
    /// Return number of ongoing file transfers
    unsigned GetNumFileTransfers() { return fileTransfers_.size(); }
    /// Return ongoing file transfers
    const std::map<StringHash, FileTransfer>& GetFileTransfers() { return fileTransfers_; }
    /// Return download directory
    const String& GetDownloadDirectory() const { return downloadDirectory_; }
    /// Return file transfer status as text
    String GetFileTransferStatus() const;
    
private:
    /// Handle network peer disconnect event
    void HandlePeerDisconnected(StringHash eventType, VariantMap& eventData);
    /// Handle file transfer complete event
    void HandleFileTransferCompleted(StringHash eventType, VariantMap& eventData);
    /// Handle file transfer failed event
    void HandleFileTransferFailed(StringHash eventType, VariantMap& eventData);
    /// Handle async scene loading finished event
    void HandleAsyncLoadFinished(StringHash eventType, VariantMap& eventData);
    /// Handle a reliable network packet
    void HandleReliablePacket(VectorBuffer& packet);
    /// Handle a challenge packet
    void HandleChallenge(VectorBuffer& packet);
    /// Handle a scene info packet
    void HandleSceneInfo(VectorBuffer& packet);
    /// Handle a file transfer packet
    void HandleTransferData(VectorBuffer& packet);
    /// Handle a file transfer failed packet
    void HandleTransferFailed(VectorBuffer& packet);
    /// Handle a join reply packet
    void HandleJoinReply(VectorBuffer& packet);
    /// Handle a full scene update from the server
    void HandleFullUpdate(VectorBuffer& packet);
    /// Handle a server update packet
    void HandleServerUpdate(VectorBuffer& packet, bool initial = false);
    /// Check whether packages need to be downloaded to join the scene
    unsigned CheckPackages();
    /// Begin a file download
    bool RequestFile(const String& fileName, unsigned size, unsigned checksum);
    /// Begin setup of the client scene
    void SetupScene();
    /// Send join scene packet after scene setup is complete
    void SendJoinScene();
    /// Send join failed event
    void JoinFailed(const String& reason);
    /// Send a client update packet
    void SendClientUpdate();
    /// Read a server update block
    void ReadNetUpdateBlock(Deserializer& source, unsigned char msgID, std::set<unsigned>& updatedNodes, std::set<unsigned>& updatedComponents);
    
    /// Scene
    SharedPtr<Scene> scene_;
    /// Server connection
    SharedPtr<Connection> serverConnection_;
    /// Network updates per second
    int netFps_;
    /// Network update time accumulator
    float timeAcc_;
    /// Client framenumber
    unsigned short frameNumber_;
    /// Scene info
    SceneInfo sceneInfo_;
    /// Ongoing file downloads
    std::map<StringHash, FileTransfer> fileTransfers_;
    /// Directory to use for downloads
    String downloadDirectory_;
    /// Downloads required to join the scene
    std::set<String> pendingDownloads_;
    /// Login data to send to the server
    VariantMap pendingLoginData_;
};
