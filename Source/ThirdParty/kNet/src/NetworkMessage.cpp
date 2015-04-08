/* Copyright The kNet Project.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */

/** @file NetworkMessage.cpp
	@brief Represents a serializable network message. */

#include <string.h>

#include "kNet/DebugMemoryLeakCheck.h"
#include "kNet/NetworkMessage.h"

namespace kNet
{

NetworkMessage::NetworkMessage()
:data(0),
priority(0),
id(0),
contentID(0),
reliable(true),
inOrder(true),
obsolete(false),
receivedPacketID(0),
messageNumber(0),
reliableMessageNumber(0),
sendCount(0),
fragmentIndex(0),
dataCapacity(0),
dataSize(0),
transfer(0)
{
}

NetworkMessage::NetworkMessage(const NetworkMessage &rhs)
{
	*this = rhs;
}

NetworkMessage &NetworkMessage::operator=(const NetworkMessage &rhs)
{
	if (this == &rhs)
		return *this;

	Resize(rhs.Size());
	memcpy(data, rhs.data, rhs.Size());
	priority = rhs.priority;
	id = rhs.id;
	contentID = rhs.contentID;
	reliable = rhs.reliable;
	inOrder = rhs.inOrder;
	obsolete = rhs.obsolete;

	// We could also copy the remaining fields messageNumber, reliableMessageNumber, sendCount and fragmentIndex,
	// but those don't have a specified meaning at the moment the message is being crafted, so don't.
	// Once the message has been queued for sending, deep copies of it will not be performed.

	return *this;
}

NetworkMessage::~NetworkMessage()
{
	delete[] data;
}

void NetworkMessage::Resize(size_t newBytes, bool discard)
{
	// Remember how much data is actually being used.
	dataSize = newBytes;

	if (newBytes <= dataCapacity)
		return; // No need to reallocate, we can fit the requested amount of bytes.

	char *newData = new char[newBytes];
	if (!discard)
		memcpy(newData, data, dataCapacity);

	delete[] data;
	data = newData;
	dataCapacity = newBytes;
}

} // ~kNet
