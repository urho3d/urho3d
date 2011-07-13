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

/** @file INetworkServerListener.h
	@brief The \ref kNet::INetworkServerListener INetworkServerListener interface. Implementable by the client application. */

namespace kNet
{

/// An interface implementable by the owner of a network server to receive notifications about connection-related events.
/// @note Do not call NetworkServer::Process from any of these methods. This might cause infinite recursion.
class INetworkServerListener
{
public:
	/// Called to query whether the new connection should be accepted or not, but only if the server operates in UDP mode.
	/// @return If the implementor of this listener decides the connection should be accepted, it should return true.
	///       If it returns false, the connection attempt will be ignored.
	virtual bool NewConnectionAttempt(const EndPoint &endPoint, const char *data, size_t numBytes)
	{
		/// @note The default implementation of this method is to accept the connection. Be sure to override this if
		///       custom access control is needed.
		return true;
	}

	/// Called to notify the listener that a new connection has been established.
	/// The application is expected to at least register a message listener for the new connection.
	virtual void NewConnectionEstablished(MessageConnection *connection) = 0;

	/// Called to notify the listener that the given client has disconnected.
	virtual void ClientDisconnected(MessageConnection *connection)
	{
		/// The default action is to not do anything.
	}
};

} // ~kNet
