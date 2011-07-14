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

#include "Object.h"
#include "VectorBuffer.h"

#include <kNetFwd.h>
#include <kNet/SharedPtr.h>

#ifdef SendMessage
#undef SendMessage
#endif

/// Connection in a networked scene
class Connection : public Object
{
    OBJECT(Connection);
    
    friend class Network;
    
public:
    /// Construct with context and kNet message connection pointers
    Connection(Context* context, kNet::SharedPtr<kNet::MessageConnection> connection);
    /// Destruct
    ~Connection();
    
    /// Send a message
    void SendMessage(int messageID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes);
    /// Send a message
    void SendMessage(int messageID, bool reliable, bool inOrder, const VectorBuffer& data);
    /// Disconnect. If wait time is non-zero, will block while waiting for disconnect to finish
    void Disconnect(int waitMSec = 0);
    
    /// Return the kNet message connection
    kNet::MessageConnection* GetMessageConnection() const;
    /// Return client identity
    const VariantMap& GetIdentity() const { return identity_; }
    /// Return whether is fully connected
    bool IsConnected() const;
    /// Return whether connection is pending
    bool IsConnectPending() const { return connectPending_; }
    /// Return remote address
    String GetAddress() const;
    /// Return remote port
    unsigned short GetPort() const;
    /// Return an address:port string
    String ToString() const;
    
private:
    /// kNet message connection
    kNet::SharedPtr<kNet::MessageConnection> connection_;
    /// Identity map
    VariantMap identity_;
    /// Connection pending flag
    bool connectPending_;
};
