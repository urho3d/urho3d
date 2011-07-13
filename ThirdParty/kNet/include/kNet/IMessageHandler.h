/* Copyright 2010 Jukka Jylänki

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */
#pragma once

/** @file IMessageHandler.h
	@brief The \ref kNet::IMessageHandler IMessageHandler interface. Implementable by the client application. */

#include "kNet/Types.h"

namespace kNet
{

class MessageConnection;

typedef unsigned long message_id_t;

/// IMessageHandler is a callback object used by the MessageConnection to invoke the main application
/// whenever a message has been received.
class IMessageHandler
{
public:
	virtual ~IMessageHandler() {}

	/// Called whenever the network stack has received a message that the application
	/// needs to process.
	virtual void HandleMessage(MessageConnection *source, message_id_t id, const char *data, size_t numBytes) = 0;

	/// Called by the network library to ask the application to produce a content ID
	/// associated with the given message. If the application returns 0, the message doesn't
	/// have a ContentID and it is processed normally.
	/// The ContentID of the message is used to determine if a message replaces another.
	virtual u32 ComputeContentID(message_id_t id, const char *data, size_t numBytes)
	{
		// The default behavior is to not have a content ID on any message.
		return 0;
	}
};

} // ~kNet
