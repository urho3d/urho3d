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
#include "Connection.h"

#include <kNet.h>

#include "DebugNew.h"

OBJECTTYPESTATIC(Connection);

Connection::Connection(Context* context, kNet::SharedPtr<kNet::MessageConnection> connection) :
    Object(context),
    connection_(connection),
    connectPending_(false)
{
}

Connection::~Connection()
{
}

void Connection::SendMessage(int messageID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes)
{
    // Make sure not to use kNet internal message ID's
    if (messageID <= 0x4 || messageID >= 0x3ffffffe)
        return;
    
    connection_->SendMessage(messageID, reliable, inOrder, 0, 0, (const char*)data, numBytes);
}

void Connection::SendMessage(int messageID, bool reliable, bool inOrder, const VectorBuffer& data)
{
    // Make sure not to use kNet internal message ID's
    if (messageID <= 0x4 || messageID >= 0x3ffffffe)
        return;
    
    connection_->SendMessage(messageID, reliable, inOrder, 0, 0, (const char*)data.GetData(), data.GetSize());
}

void Connection::Disconnect(int waitMSec)
{
    connection_->Disconnect(waitMSec);
}

kNet::MessageConnection* Connection::GetMessageConnection() const
{
    return const_cast<kNet::MessageConnection*>(connection_.ptr());
}

bool Connection::IsConnected() const
{
    return connection_->GetConnectionState() == kNet::ConnectionOK;
}

String Connection::GetAddress() const
{
    kNet::Socket* socket = const_cast<kNet::MessageConnection*>(connection_.ptr())->GetSocket();
    return socket ? String(socket->DestinationAddress()) : String();
}

unsigned short Connection::GetPort() const
{
    kNet::Socket* socket = const_cast<kNet::MessageConnection*>(connection_.ptr())->GetSocket();;
    return socket ? socket->DestinationPort() : 0;
}

String Connection::ToString() const
{
    return GetAddress() + ":" + String(GetPort());
}
