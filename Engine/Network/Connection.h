//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "HashSet.h"
#include "Object.h"
#include "ReplicationState.h"
#include "Timer.h"
#include "VectorBuffer.h"

#include <kNetFwd.h>
#include <kNet/SharedPtr.h>

#ifdef SendMessage
#undef SendMessage
#endif

class File;
class MemoryBuffer;
class Node;
class Scene;
class Serializable;

/// Queued remote event.
struct RemoteEvent
{
    /// Receiver node ID (0 if not a remote node event.)
    unsigned receiverID_;
    /// Event type.
    StringHash eventType_;
    /// Event data.
    VariantMap eventData_;
    /// In order flag.
    bool inOrder_;
};

/// Package file receive transfer.
struct PackageDownload
{
    /// Construct with defaults.
    PackageDownload();
    
    /// Destination file.
    SharedPtr<File> file_;
    /// Already received fragments.
    HashSet<unsigned> receivedFragments_;
    /// Package name.
    String name_;
    /// Total number of fragments.
    unsigned totalFragments_;
    /// Checksum.
    unsigned checksum_;
    /// Download initiated flag.
    bool initiated_;
};

/// Package file send transfer.
struct PackageUpload
{
    /// Construct with defaults.
    PackageUpload();
    
    /// Source file.
    SharedPtr<File> file_;
    /// Current fragment index.
    unsigned fragment_;
    /// Total number of fragments
    unsigned totalFragments_;
};

/// %Connection to a remote network host.
class Connection : public Object
{
    OBJECT(Connection);
    
public:
    /// Construct with context and kNet message connection pointers.
    Connection(Context* context, bool isClient, kNet::SharedPtr<kNet::MessageConnection> connection);
    /// Destruct.
    ~Connection();
    
    /// Send a message.
    void SendMessage(int msgID, bool reliable, bool inOrder, const VectorBuffer& msg, unsigned contentID = 0);
    /// Send a message.
    void SendMessage(int msgID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes, unsigned contentID = 0);
    /// Send a remote event.
    void SendRemoteEvent(StringHash eventType, bool inOrder, const VariantMap& eventData = VariantMap());
    /// Send a remote node event.
    void SendRemoteEvent(Node* receiver, StringHash eventType, bool inOrder, const VariantMap& eventData = VariantMap());
    /// Assign scene. On the server, this will cause the client to load it.
    void SetScene(Scene* newScene);
    /// Assign identity. Called by Network.
    void SetIdentity(const VariantMap& identity);
    /// %Set new controls.
    void SetControls(const Controls& newControls);
    /// %Set the observer position for interest management.
    void SetPosition(const Vector3& position);
    /// %Set the connection pending status. Called by Network.
    void SetConnectPending(bool connectPending);
    /// %Set whether to log data in/out statistics.
    void SetLogStatistics(bool enable);
    /// Disconnect. If wait time is non-zero, will block while waiting for disconnect to finish.
    void Disconnect(int waitMSec = 0);
    /// Send scene update messages. Called by Network.
    void SendServerUpdate();
    /// Send latest controls from the client. Called by Network.
    void SendClientUpdate();
    /// Send queued remote events. Called by Network.
    void SendRemoteEvents();
    /// Send package files to client. Called by network.
    void SendPackages();
    /// Process pending latest data for nodes and components.
    void ProcessPendingLatestData();
    /// Process a LoadScene message from the server. Called by Network.
    void ProcessLoadScene(int msgID, MemoryBuffer& msg);
    /// Process a SceneChecksumError message from the server. Called by Network.
    void ProcessSceneChecksumError(int msgID, MemoryBuffer& msg);
    /// Process a scene update message from the server. Called by Network.
    void ProcessSceneUpdate(int msgID, MemoryBuffer& msg);
    /// Process package download related messages. Called by Network.
    void ProcessPackageDownload(int msgID, MemoryBuffer& msg);
    /// Process an Identity message from the client. Called by Network.
    void ProcessIdentity(int msgID, MemoryBuffer& msg);
    /// Process a Controls message from the client. Called by Network.
    void ProcessControls(int msgID, MemoryBuffer& msg);
    /// Process a SceneLoaded message from the client. Called by Network.
    void ProcessSceneLoaded(int msgID, MemoryBuffer& msg);
    /// Process a remote event message from the client or server. Called by Network.
    void ProcessRemoteEvent(int msgID, MemoryBuffer& msg);
    
    /// Return the kNet message connection.
    kNet::MessageConnection* GetMessageConnection() const;
    /// Return client identity.
    const VariantMap& GetIdentity() const { return identity_; }
    /// Return the scene used by this connection.
    Scene* GetScene() const;
    /// Return the client controls of this connection.
    const Controls& GetControls() const { return controls_; }
    /// Return the observer position for interest management.
    const Vector3& GetPosition() const { return position_; }
    /// Return whether is a client connection.
    bool IsClient() const { return isClient_; }
    /// Return whether is fully connected.
    bool IsConnected() const;
    /// Return whether connection is pending.
    bool IsConnectPending() const { return connectPending_; }
    /// Return whether the scene is loaded and ready to receive server updates.
    bool IsSceneLoaded() const { return sceneLoaded_; }
    /// Return whether to log data in/out statistics.
    bool GetLogStatistics() const { return logStatistics_; }
    /// Return remote address.
    String GetAddress() const;
    /// Return remote port.
    unsigned short GetPort() const;
    /// Return an address:port string.
    String ToString() const;
    /// Return number of package downloads remaining.
    unsigned GetNumDownloads() const;
    /// Return name of current package download, or empty if no downloads.
    const String& GetDownloadName() const;
    /// Return progress of current package download, or 1.0 if no downloads.
    float GetDownloadProgress() const;
    
    /// Observer position for interest management.
    Vector3 position_;
    /// Current controls.
    Controls controls_;
    /// Identity map.
    VariantMap identity_;
    
private:
    /// Handle scene loaded event.
    void HandleAsyncLoadFinished(StringHash eventType, VariantMap& eventData);
    /// Process a node for sending a network update. Recurses to process depended on node(s) first.
    void ProcessNode(unsigned nodeID);
    /// Process a node that the client has not yet received.
    void ProcessNewNode(Node* node);
    /// Process a node that the client has already received.
    void ProcessExistingNode(Node* node, NodeReplicationState& nodeState);
    /// Initiate a package download.
    void RequestPackage(const String& name, unsigned fileSize, unsigned checksum);
    /// Send an error reply for a package download.
    void SendPackageError(const String& name);
    /// Handle scene load failure on the server or client.
    void OnSceneLoadFailed();
    /// Handle a package download failure on the client.
    void OnPackageDownloadFailed(const String& name);
    /// Handle all packages loaded successfully. Also called directly on MSG_LOADSCENE if there are none.
    void OnPackagesReady();
    
    /// kNet message connection.
    kNet::SharedPtr<kNet::MessageConnection> connection_;
    /// Scene.
    WeakPtr<Scene> scene_;
    /// Network replication state of the scene.
    SceneReplicationState sceneState_;
    /// Waiting or ongoing package file receive transfers.
    HashMap<StringHash, PackageDownload> downloads_;
    /// Ongoing package send transfers.
    HashMap<StringHash, PackageUpload> uploads_;
    /// Pending latest data for not yet received nodes.
    HashMap<unsigned, PODVector<unsigned char> > nodeLatestData_;
    /// Pending latest data for not yet received components.
    HashMap<unsigned, PODVector<unsigned char> > componentLatestData_;
    /// Node ID's to process during a replication update.
    HashSet<unsigned> nodesToProcess_;
    /// Reusable message buffer.
    VectorBuffer msg_;
    /// Queued remote events.
    Vector<RemoteEvent> remoteEvents_;
    /// Scene file to load once all packages (if any) have been downloaded.
    String sceneFileName_;
    /// Statistics timer.
    Timer statsTimer_;
    /// Client connection flag.
    bool isClient_;
    /// Connection pending flag.
    bool connectPending_;
    /// Scene loaded flag.
    bool sceneLoaded_;
    /// Show statistics flag.
    bool logStatistics_;
};
