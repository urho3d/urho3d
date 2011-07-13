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

/** @file kNetFwd.h
	@brief Forward-declares all common symbols defined by kNet. */

namespace kNet
{
	class Clock;
	class DataDeserializer;
	struct Datagram;
	class DataSerializer;
	struct EndPoint;
	class Event;
	class EventArray;
	class IMessageHandler;
	class INetworkServerListener;
	class MessageConnection;
	class MessageListParser;
	class NetException;
	class Network;
	class NetworkMessage;
	class NetworkServer;
	class PolledTimer;
	class SerializationStructCompiler;
	class SerializedDataIterator;
	class Socket;
	class StatsEventHierarchyNode;
	class TCPMessageConnection;
	class Thread;
	class UDPMessageConnection;
}
